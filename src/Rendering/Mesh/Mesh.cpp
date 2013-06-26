
#include "Mesh.hpp"
#include <algorithm>
#include <stdexcept>


Mesh::Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer):
    vertexBuffer_(vertexBuffer), indexBuffer_(nullptr)
{
    generateDefaultTriangles();
}



Mesh::Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer,
           const std::shared_ptr<IndexBuffer>& indexBuffer):
    vertexBuffer_(vertexBuffer), indexBuffer_(indexBuffer)
{}



void Mesh::initialize(GLuint program)
{
    vertexBuffer_->initialize(program);
    if (indexBuffer_)
        indexBuffer_->initialize(program);
}



void Mesh::store()
{
    vertexBuffer_->store();
    if (indexBuffer_)
        indexBuffer_->store();
}



void Mesh::enable()
{
    vertexBuffer_->enable();
    if (indexBuffer_)
        indexBuffer_->enable();
}



void Mesh::disable()
{
    vertexBuffer_->disable();
    if (indexBuffer_)
        indexBuffer_->disable();
}



bool Mesh::draw(GLenum mode)
{
    //indexBuffer is drawn with priority iff it is available
    if (indexBuffer_)
        indexBuffer_->draw(mode);
    else
        vertexBuffer_->draw(mode);
}



std::vector<glm::vec3> Mesh::getVertices()
{
    return vertexBuffer_->getVertices();
}



std::vector<Triangle> Mesh::getTriangles()
{
    if (!indexBuffer_)
        return defaultTriangles_;
    return indexBuffer_->getTriangles();
}



void Mesh::generateDefaultTriangles()
{
    unsigned long vCount = vertexBuffer_->getVertices().size();
    if (vCount % 3 != 0)
        throw std::runtime_error("VertexBuffer not divisible into triangles!");

    defaultTriangles_.reserve(vCount / 3);
    unsigned int vertexIndex = 0;
    std::generate(defaultTriangles_.begin(), defaultTriangles_.end(),
        [&]()
        {
            Triangle tri(vertexIndex, vertexIndex + 1, vertexIndex + 2);
            vertexIndex += 3;
            return tri;
        }
    );
}
