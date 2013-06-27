
#include "Model.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <algorithm>
#include <iostream>

/*
Model::Model(const std::shared_ptr<Mesh>& mesh):
    mesh_(mesh), modelMatrix_(glm::mat4()),
    isVisible_(true), beenInitialized_(false), renderMode_(GL_TRIANGLES)
{}
*/


Model::Model(const std::shared_ptr<Mesh>& mesh,
    const std::vector<std::shared_ptr<OptionalDataBuffer>>& optionalDBs):
    Model(mesh, optionalDBs, GL_TRIANGLES)
{}



Model::Model(const std::shared_ptr<Mesh>& mesh,
    const std::vector<std::shared_ptr<OptionalDataBuffer>>& optionalDBs,
    GLenum renderMode):
    mesh_(mesh), optionalDBs_(optionalDBs), modelMatrix_(glm::mat4()),
    isVisible_(true), beenInitialized_(false), renderMode_(renderMode)
{} //Scene will call initializeAndStore



void Model::initializeAndStore(std::shared_ptr<cs5400::Program> program)
{
    renderingProgram_ = program;

    mesh_->initialize(program->getHandle());
    mesh_->store();

    for_each (optionalDBs_.begin(), optionalDBs_.end(),
        [&](const std::shared_ptr<OptionalDataBuffer>& buffer)
        {
            buffer->initialize(program->getHandle());
            buffer->store();
        });

    beenInitialized_ = true;
}



// Objects that are not 'visible' will not be rendered
void Model::setVisible(bool visible)
{
    isVisible_ = visible;
}



// Set the matrix to convert from model coords to world coords
void Model::setModelMatrix(const glm::mat4& matrix)
{
    modelMatrix_ = matrix;
}



void Model::setRenderMode(GLenum newMode)
{
    renderMode_ = newMode;
}



std::shared_ptr<cs5400::Program> Model::getProgram()
{
    if (!beenInitialized_)
        throw std::runtime_error("Model has not been initialized!");

    return renderingProgram_;
}



std::vector<std::shared_ptr<OptionalDataBuffer>> Model::getOptionalDataBuffers()
{
    return optionalDBs_;
}



bool Model::hasBeenInitialized()
{
    return beenInitialized_;
}



// Render the object
void Model::render(GLint modelMatrixID)
{
    if (modelMatrixID < 0)
        throw std::runtime_error("Invalid handle passed to Model!");

    if (!beenInitialized_)
        throw std::runtime_error("Model has not been initialized!");

    if (isVisible_)
    {
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix_));

        enableDataBuffers();
        mesh_->draw(renderMode_);
        disableDataBuffers();
    }
}



void Model::enableDataBuffers()
{
    mesh_->enable();

    for_each (optionalDBs_.begin(), optionalDBs_.end(),
        [&](const std::shared_ptr<OptionalDataBuffer>& buffer)
        {
            buffer->enable();
        });
}



void Model::disableDataBuffers()
{
    mesh_->disable();

    for_each (optionalDBs_.begin(), optionalDBs_.end(),
        [&](const std::shared_ptr<OptionalDataBuffer>& buffer)
        {
            buffer->disable();
        });
}
