
#include "VertexBuffer.hpp"
#include <algorithm>


VertexBuffer::VertexBuffer(const std::vector<glm::vec3>& vertices):
    vertices_(vertices)
{}



void VertexBuffer::initialize(GLuint program)
{
    glGenBuffers(1, &vertexBuffer_);
    vertexAttrib_ = glGetAttribLocation(program, "vertex");
}



// Store the vertices in a GPU buffer
void VertexBuffer::store()
{
    std::vector<GLfloat> rawPoints;
    for_each (vertices_.begin(), vertices_.end(),
        [&](const glm::vec3& vert)
        {
            rawPoints.push_back(vert.x);
            rawPoints.push_back(vert.y);
            rawPoints.push_back(vert.z);
        });

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
    glBufferData(GL_ARRAY_BUFFER, rawPoints.size() * sizeof(GLfloat),
        rawPoints.data(), GL_STATIC_DRAW);
}



void VertexBuffer::enable()
{
    glEnableVertexAttribArray(vertexAttrib_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
    glVertexAttribPointer(vertexAttrib_, 3, GL_FLOAT, GL_FALSE, 0, 0);
}



void VertexBuffer::disable()
{
    glDisableVertexAttribArray(vertexAttrib_);
}



void VertexBuffer::draw(GLenum mode)
{
    glDrawElements(mode, (int)vertices_.size() * 3, GL_UNSIGNED_INT, 0);
}


#include <iostream>
std::vector<glm::vec3> VertexBuffer::getVertices()
{
    std::cout << vertices_[0].x << " " << vertices_[0].y << " " << vertices_[0].z << std::endl;
    std::cout << vertices_[1].x << " " << vertices_[1].y << " " << vertices_[1].z << std::endl;
    std::cout << vertices_[2].x << " " << vertices_[2].y << " " << vertices_[2].z << std::endl;
    return vertices_;
}



std::shared_ptr<ShaderSnippet> VertexBuffer::getVertexShaderGLSL()
{
    return std::make_shared<ShaderSnippet>();
}



std::shared_ptr<ShaderSnippet> VertexBuffer::getFragmentShaderGLSL()
{
    return std::make_shared<ShaderSnippet>();
}
