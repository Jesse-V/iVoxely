
#include "RenderableObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <algorithm>
#include <iostream>


RenderableObject::RenderableObject(const std::shared_ptr<Mesh>& mesh,
    const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs):
    RenderableObject(mesh, optionalDBs, GL_TRIANGLES)
{}



RenderableObject::RenderableObject(const std::shared_ptr<Mesh>& mesh,
    const std::vector<std::shared_ptr<DataBuffer>>& optionalDBs,
    GLenum renderMode):
    mesh_(mesh), dataBuffers_(optionalDBs), modelMatrix_(glm::mat4()),
    isVisible_(true), beenInitialized_(false), renderMode_(renderMode)
{} //Scene will call initializeAndStore



void RenderableObject::initializeAndStore(std::shared_ptr<cs5400::Program> program)
{
    renderingProgram_ = program;

    mesh_->initialize(program->getHandle());
    mesh_->store();

    for_each (dataBuffers_.begin(), dataBuffers_.end(),
        [&](const std::shared_ptr<DataBuffer>& buffer)
        {
            buffer->initialize(program->getHandle());
            buffer->store();
        });

    beenInitialized_ = true;
}



// Objects that are not 'visible' will not be rendered
void RenderableObject::setVisible(bool visible)
{
    isVisible_ = visible;
}



// Set the matrix to convert from model coords to world coords
void RenderableObject::setModelMatrix(const glm::mat4& matrix)
{
    modelMatrix_ = matrix;
}



void RenderableObject::setRenderMode(GLenum newMode)
{
    renderMode_ = newMode;
}



std::shared_ptr<cs5400::Program> RenderableObject::getProgram()
{
    if (!beenInitialized_)
        throw std::runtime_error("RenderableObject has not been initialized!");

    return renderingProgram_;
}



std::vector<std::shared_ptr<DataBuffer>> RenderableObject::getAllDataBuffers()
{
    std::vector<std::shared_ptr<DataBuffer>> all(dataBuffers_);
    all.insert(all.begin(), mesh_);
    return all;
}



bool RenderableObject::hasBeenInitialized()
{
    return beenInitialized_;
}



// Render the object
void RenderableObject::render(GLint modelMatrixID)
{
    if (modelMatrixID < 0)
        throw std::runtime_error("Invalid handle passed to RenderableObject!");

    if (!beenInitialized_)
        throw std::runtime_error("RenderableObject has not been initialized!");

    if (isVisible_)
    {
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix_));

        enableDataBuffers();
        drawDataBuffers();
        disableDataBuffers();
    }
}



void RenderableObject::enableDataBuffers()
{
    mesh_->enable();

    for_each (dataBuffers_.begin(), dataBuffers_.end(),
        [&](const std::shared_ptr<DataBuffer>& buffer)
        {
            buffer->enable();
        });
}



void RenderableObject::drawDataBuffers()
{
    bool optionalBufferRendered = false;

    for_each (dataBuffers_.begin(), dataBuffers_.end(),
    [&](const std::shared_ptr<DataBuffer>& buffer)
    {
        if (buffer->draw(GL_TRIANGLES))
            optionalBufferRendered = true;
    });

    if (!optionalBufferRendered)
        mesh_->draw(GL_TRIANGLES);
}



void RenderableObject::disableDataBuffers()
{
    mesh_->disable();

    for_each (dataBuffers_.begin(), dataBuffers_.end(),
        [&](const std::shared_ptr<DataBuffer>& buffer)
        {
            buffer->disable();
        });
}
