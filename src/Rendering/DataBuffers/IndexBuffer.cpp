
#include "IndexBuffer.hpp"
#include <algorithm>


IndexBuffer::IndexBuffer(const std::vector<Triangle>& triangles):
	triangles(triangles)
{}



void IndexBuffer::initialize(GLuint)
{
	glGenBuffers(1, &meshBuffer);
}



void IndexBuffer::store()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * 3 * sizeof(GLuint), triangles.data(), GL_STATIC_DRAW);
}



void IndexBuffer::enable()
{}



void IndexBuffer::disable()
{}



bool IndexBuffer::draw(GLenum mode)
{
	glDrawElements(mode, (int)triangles.size() * 3, GL_UNSIGNED_INT, 0);
	return true;
}



std::shared_ptr<VertexShaderSnippet> IndexBuffer::getVertexShaderGLSL()
{
	return std::make_shared<VertexShaderSnippet>();
}



std::shared_ptr<FragmentShaderSnippet> IndexBuffer::getFragmentShaderGLSL()
{
	return std::make_shared<FragmentShaderSnippet>();
}
