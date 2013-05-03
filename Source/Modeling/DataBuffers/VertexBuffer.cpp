
#include "VertexBuffer.hpp"
#include <algorithm>
#include <iostream>


VertexBuffer::VertexBuffer(const std::shared_ptr<Mesh>& mesh):
	mesh(mesh)
{}



void VertexBuffer::initialize(GLuint program)
{
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &normalBuffer);
	glGenBuffers(1, &meshBuffer);
	vertexAttrib = glGetAttribLocation(program, "vertex"); //get attributes
	normalAttrib = glGetAttribLocation(program, "vertexNormal");
}



void VertexBuffer::store()
{
	std::cout << "Sending to GPU... ";

	std::cout << "points... ";
	storePoints();

	std::cout << "normals... ";
	storeNormals();

	std::cout << "mesh... ";
	storeMesh();

	std::cout << "done" << std::endl;
}



void VertexBuffer::enable()
{
	enableVertices();
	enableNormals();

	glDrawElements(GL_TRIANGLES, mesh->triangles.size() * 3, GL_UNSIGNED_INT, 0);
}



void VertexBuffer::disable()
{
	glDisableVertexAttribArray(vertexAttrib);
	glDisableVertexAttribArray(normalAttrib);
}


//-----------------------private methods---------------------------


// Store the vertices in a GPU buffer
void VertexBuffer::storePoints()
{
	const std::vector<glm::vec3> &verts = mesh->vertices;

	std::vector<GLfloat> rawPoints;
	for_each (verts.begin(), verts.end(),
		[&](const glm::vec3& vert)
		{
			rawPoints.push_back(vert.x);
			rawPoints.push_back(vert.y);
			rawPoints.push_back(vert.z);
		});

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, rawPoints.size() * sizeof(GLfloat), rawPoints.data(), GL_STATIC_DRAW);
}



// Store the normals in a GPU buffer
void VertexBuffer::storeNormals()
{
	std::vector<GLfloat> rawNormals;
	for_each (mesh->normals.begin(), mesh->normals.end(),
		[&](const glm::vec3& norm)
		{
			rawNormals.push_back(norm.x);
			rawNormals.push_back(norm.y);
			rawNormals.push_back(norm.z);
		});

	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, rawNormals.size() * sizeof(GLfloat), rawNormals.data(), GL_STATIC_DRAW);
}



// Store the mesh in a GPU buffer
void VertexBuffer::storeMesh()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->triangles.size() * 3 * sizeof(GLuint), mesh->triangles.data(), GL_STATIC_DRAW);
}



void VertexBuffer::enableVertices()
{
	glEnableVertexAttribArray(vertexAttrib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(vertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}



void VertexBuffer::enableNormals()
{
	glEnableVertexAttribArray(normalAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
