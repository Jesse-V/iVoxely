
#include "VertexBuffer.hpp"
#include <algorithm>
#include <iostream>


VertexBuffer::VertexBuffer(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles):
	vertices(vertices), triangles(triangles)
{}



void VertexBuffer::initialize(GLuint program)
{
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &meshBuffer);
	vertexAttrib = glGetAttribLocation(program, "vertex"); //get attributes
}



void VertexBuffer::store()
{
	std::cout << "Sending to GPU... ";

	std::cout << "points... ";
	storePoints();

	std::cout << "mesh... ";
	storeMesh();

	std::cout << "done" << std::endl;
}



void VertexBuffer::enable()
{
	enableVertices();

	glDrawElements(GL_TRIANGLES, (int)triangles.size() * 3, GL_UNSIGNED_INT, 0);
}



void VertexBuffer::disable()
{
	glDisableVertexAttribArray(vertexAttrib);

}


//-----------------------private methods---------------------------


// Store the vertices in a GPU buffer
void VertexBuffer::storePoints()
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



// Store the triangles in a GPU buffer
void VertexBuffer::storeMesh()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * 3 * sizeof(GLuint), triangles.data(), GL_STATIC_DRAW);
}



void VertexBuffer::enableVertices()
{
	glEnableVertexAttribArray(vertexAttrib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(vertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
