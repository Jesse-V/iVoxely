
#include "IndexBuffer.hpp"
#include <algorithm>


IndexBuffer::IndexBuffer(const std::vector<Triangle>& triangles):
    triangles_(triangles)
{}



void IndexBuffer::initialize(GLuint)
{
    glGenBuffers(1, &meshBuffer_);
}



void IndexBuffer::store()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshBuffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles_.size() * 3 * sizeof(GLuint),
        triangles_.data(), GL_STATIC_DRAW);
}



void IndexBuffer::enable()
{}



void IndexBuffer::disable()
{}



void IndexBuffer::draw(GLenum mode)
{
    glDrawElements(mode, (int)triangles_.size() * 3, GL_UNSIGNED_INT, 0);
}



std::vector<Triangle> IndexBuffer::getTriangles()
{
    return triangles_;
}



SnippetPtr IndexBuffer::getVertexShaderGLSL()
{
    return std::make_shared<ShaderSnippet>();
}



SnippetPtr IndexBuffer::getFragmentShaderGLSL()
{
    return std::make_shared<ShaderSnippet>();
}
