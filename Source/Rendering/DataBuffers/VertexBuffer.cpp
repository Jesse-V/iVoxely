
#include "VertexBuffer.hpp"
#include <algorithm>
#include <iostream>


VertexBuffer::VertexBuffer(const std::vector<glm::vec3>& vertices):
	vertices(vertices)
{}



void VertexBuffer::initialize(GLuint program)
{
	glGenBuffers(1, &vertexBuffer);
	vertexAttrib = glGetAttribLocation(program, VERTEX_ATTRIB_NAME);
}



// Store the vertices in a GPU buffer
void VertexBuffer::store()
{
	std::vector<GLfloat> rawPoints;
	for_each (vertices.begin(), vertices.end(),
		[&](const glm::vec3& vert)
		{
			rawPoints.push_back(vert.x);
			rawPoints.push_back(vert.y);
			rawPoints.push_back(vert.z);
		});

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, rawPoints.size() * sizeof(GLfloat), rawPoints.data(), GL_STATIC_DRAW);
}



void VertexBuffer::enable()
{
	glEnableVertexAttribArray(vertexAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(vertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}



void VertexBuffer::disable()
{
	glDisableVertexAttribArray(vertexAttrib);
}



bool VertexBuffer::draw(GLenum mode)
{
	glDrawElements(mode, (int)vertices.size() * 3, GL_UNSIGNED_INT, 0);
	return true;
}
