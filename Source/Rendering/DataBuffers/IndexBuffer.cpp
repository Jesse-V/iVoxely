
#include "IndexBuffer.hpp"
#include <algorithm>
#include <iostream>


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
{
	glDrawElements(GL_TRIANGLES, (int)triangles.size() * 3, GL_UNSIGNED_INT, 0); //todo: could go somewhere else? Could be changed to draw vertices instead of triangles
}



void IndexBuffer::disable()
{}
