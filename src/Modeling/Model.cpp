
#include "Model.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <algorithm>
#include <iostream>


Model::Model(const std::shared_ptr<Mesh>& mesh):
    mesh_(mesh), modelMatrix_(glm::mat4()),
    isVisible_(true), renderMode_(GL_TRIANGLES)
{}



Model::Model(const std::shared_ptr<Mesh>& mesh, const BufferList& optionalDBs):
    Model(mesh, optionalDBs, GL_TRIANGLES)
{}



Model::Model(const std::shared_ptr<Mesh>& mesh, const BufferList& optionalDBs,
    GLenum renderMode):
    mesh_(mesh), optionalDBs_(optionalDBs), modelMatrix_(glm::mat4()),
    isVisible_(true), renderMode_(renderMode)
{
    /*
    std::cout << "Created a Model with { ";
    for_each (optionalDBs_.begin(), optionalDBs_.end(),
        [&](const std::shared_ptr<OptionalDataBuffer>& buffer)
        {
            std::cout << typeid(*buffer).name() << " ";
        }
    );

    std::cout << "} OptionalDataBuffers." << std::endl;
    */
} //Scene will call saveAs



void Model::saveAs(const ProgramPtr& program)
{
    std::cout << "Storing mesh and model data as program #" <<
        program->getHandle() << "... " << std::endl;

    mesh_->initialize(program->getHandle());
    mesh_->store();

    std::cout << "Stored " << typeid(*mesh_).name() << ". ";
    checkGlError();

    for_each (optionalDBs_.begin(), optionalDBs_.end(),
        [&](const std::shared_ptr<OptionalDataBuffer>& buffer)
        {
            buffer->initialize(program->getHandle());
            buffer->store();

            std::cout << "Stored " << typeid(*buffer).name() << ": ";
            checkGlError();
        });

    std::cout << ".. done saving program." << std::endl;
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



BufferList Model::getOptionalDataBuffers()
{
    return optionalDBs_;
}



// Render the object
void Model::render(GLint modelMatrixID)
{
    if (modelMatrixID < 0)
        throw std::runtime_error("Invalid handle passed to Model!");

    //if (!isStoredOnGPU_)
    //    throw std::runtime_error("Model has not been initialized!");

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
