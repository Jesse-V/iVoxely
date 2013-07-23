
#include "IndexBuffer.hpp"
#include <algorithm>
#include <stdexcept>


IndexBuffer::IndexBuffer(const std::vector<Triangle>& triangles)
{
    indices.reserve(triangles.size() * 3);

    for_each (triangles.begin(), triangles.end(), [&](const Triangle& triangle)
    {
        indices.push_back(triangle.a);
        indices.push_back(triangle.b);
        indices.push_back(triangle.c);
    });
}



IndexBuffer::IndexBuffer(const std::vector<Quad>& quads)
{
    indices.reserve(quads.size() * 4);

    for_each (quads.begin(), quads.end(), [&](const Quad& quad)
    {
        indices.push_back(quad.a);
        indices.push_back(quad.b);
        indices.push_back(quad.c);
        indices.push_back(quad.d);
    });
}



void IndexBuffer::initialize(GLuint)
{
    glGenBuffers(1, &meshBuffer_);
}



void IndexBuffer::store()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshBuffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        indices.data(), GL_STATIC_DRAW);
}



void IndexBuffer::enable()
{}



void IndexBuffer::disable()
{}



void IndexBuffer::draw(GLenum mode)
{
    glDrawElements(mode, (int)indices.size(), GL_UNSIGNED_INT, 0);
}



std::vector<Triangle> IndexBuffer::reinterpretAsTriangles()
{
    if (indices.size() % 3 != 0)
        throw std::runtime_error("Cannot reinterpret indices as Triangles!");

    static std::vector<Triangle> triangles;

    if (triangles.size() != 0)
        return triangles; //if already reinterpreted, just return it

    //else, reserve the space and convert
    triangles.reserve(indices.size() / 3);

    for (std::size_t j = 0; j < indices.size(); j += 3)
    {
        Triangle triangle(indices[j], indices[j + 1], indices[j + 2]);
        triangles.push_back(triangle);
    }

    return triangles;
}



std::vector<Quad> IndexBuffer::reinterpretAsQuads()
{
    if (indices.size() % 4 != 0)
        throw std::runtime_error("Cannot reinterpret indices as Quads!");

    static std::vector<Quad> quads;

    if (quads.size() != 0)
        return quads; //if already reinterpreted, just return it

    //else, reserve the space and convert
    quads.reserve(indices.size() / 4);

    for (std::size_t j = 0; j < indices.size(); j += 4)
    {
        Quad quad(indices[j], indices[j + 1], indices[j + 2], indices[j + 3]);
        quads.push_back(quad);
    }

    return quads;
}



SnippetPtr IndexBuffer::getVertexShaderGLSL()
{
    return std::make_shared<ShaderSnippet>();
}



SnippetPtr IndexBuffer::getFragmentShaderGLSL()
{
    return std::make_shared<ShaderSnippet>();
}
