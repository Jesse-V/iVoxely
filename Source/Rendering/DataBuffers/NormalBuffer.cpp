
#include "NormalBuffer.hpp"
#include <algorithm>


NormalBuffer::NormalBuffer(const std::vector<glm::vec3>& normals):
	normals(normals)
{}



void NormalBuffer::initialize(GLuint program)
{
	glGenBuffers(1, &normalBuffer);
	normalAttrib = glGetAttribLocation(program, NORMAL_ATTRIB_NAME);
}



// Store the normals in a GPU buffer
void NormalBuffer::store()
{
	std::vector<GLfloat> rawNormals;
	for_each (normals.begin(), normals.end(),
		[&](const glm::vec3& norm)
		{
			rawNormals.push_back(norm.x);
			rawNormals.push_back(norm.y);
			rawNormals.push_back(norm.z);
		});

	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, rawNormals.size() * sizeof(GLfloat), rawNormals.data(), GL_STATIC_DRAW);
}



void NormalBuffer::enable()
{
	glEnableVertexAttribArray(normalAttrib);
	//glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}



void NormalBuffer::disable()
{
	glDisableVertexAttribArray(normalAttrib);
}


//------------------static normal-calculation methods----------------------


// Calculate the normals for a given mesh using the
// "Mean Weighted by Angle" (MWA) algorithm as seen in the paper
// "A Comparison of Algorithms for Vertex Normal Computation"
std::vector<glm::vec3> NormalBuffer::calcNormalsMWA(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles)
{
	// keep track of which triangles a given vertex is part of
	std::vector<std::vector<size_t>> vtmap;
	vtmap.resize(vertices.size());

	std::vector<glm::vec3> tN = calculateTriangleNormals(vertices, triangles, vtmap);
	std::vector<glm::vec3> normals;

	// Now calculate the vertex normals
	for (size_t i = 0; i < vertices.size(); i++)
	{
		const std::vector<size_t>& tlist = vtmap[i];

		glm::vec3 normal(0.0f, 0.0f, 0.0f);

		for (size_t k = 0; k < tlist.size(); k++)
		{
			const Triangle& t = triangles[tlist[k]];
			const glm::vec3& p1 = vertices[t.a];
			const glm::vec3& p2 = vertices[t.b];
			const glm::vec3& p3 = vertices[t.c];

			glm::vec3 edge1 = p2 - p1;
			glm::vec3 edge2 = p3 - p1;
			glm::vec3 edgecross = glm::cross(edge2, edge1);

			float sinalpha = glm::length(edgecross) / (glm::length(edge1) * glm::length(edge2));
			float alpha = (float)asin(sinalpha);

			normal += alpha * tN[tlist[k]];
		}

		normals.push_back(glm::normalize(normal));
	}

	return normals;
}


// Calculate the normals of the mesh using the
// "Mean Weighted Average By Sine And Edge Reciprocal" (MWASER) algorithm as seen in
// "A Comparison of Algorithms for Vertex Normal Computation"
std::vector<glm::vec3> NormalBuffer::calcNormalsMWASER(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles)
{
	// keep track of which triangles a given vertex is part of
	std::vector<std::vector<size_t>> vtmap;
	vtmap.resize(vertices.size());

	std::vector<glm::vec3> tN = calculateTriangleNormals(vertices, triangles, vtmap);
	std::vector<glm::vec3> normals;

	// Now calculate the vertex normals
	for (size_t i = 0; i < vertices.size(); i++)
	{
		const std::vector<size_t>& tlist = vtmap[i];

		glm::vec3 normal(0.0f, 0.0f, 0.0f);

		for (size_t k = 0; k < tlist.size(); k++)
		{
			const Triangle& t = triangles[tlist[k]];
			const glm::vec3& p1 = vertices[t.a];
			const glm::vec3& p2 = vertices[t.b];
			const glm::vec3& p3 = vertices[t.c];

			glm::vec3 edge1 = p2 - p1;
			glm::vec3 edge2 = p3 - p1;
			glm::vec3 edgecross = glm::cross(edge1, edge2);

			float edge1len = glm::length(edge1);
			float edge2len = glm::length(edge2);
			float sinalpha = glm::length(edgecross) / (edge1len * edge2len);

			normal += sinalpha * tN[tlist[k]] / (edge1len * edge2len);
		}

		normals.push_back(glm::normalize(normal));
	}

	return normals;
}


// Calculate the normals for a given mesh using the
// "Mean Weighted Equally" (MWE) algorithm (Naive approach)
std::vector<glm::vec3> NormalBuffer::calcNormalsMWE(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles)
{
	// keep track of which triangles a given vertex is part of
	std::vector<std::vector<size_t>> vtmap;
	vtmap.resize(vertices.size());

	std::vector<glm::vec3> tN = calculateTriangleNormals(vertices, triangles, vtmap);
	std::vector<glm::vec3> normals;

	// Now calculate the vertex normals
	for (size_t i = 0; i < vertices.size(); i++)
	{
		const std::vector<size_t>& tlist = vtmap[i];

		glm::vec3 normal(0.0f, 0.0f, 0.0f);
		for (size_t k = 0; k < tlist.size(); k++)
			normal += tN[tlist[k]];

		normals.push_back(glm::normalize(normal));
	}

	return normals;
}



std::vector<glm::vec3> NormalBuffer::calculateTriangleNormals(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles, std::vector<std::vector<size_t>>& vtmap)
{
	std::vector<glm::vec3> tN;

	for (size_t i = 0; i < triangles.size(); i++)
	{
		const Triangle& t = triangles[i];
		const glm::vec3& a = vertices[t.a];
		const glm::vec3& b = vertices[t.b];
		const glm::vec3& c = vertices[t.c];
		tN.push_back(glm::cross(b - a, c - a));

		vtmap[t.a].push_back(i);
		vtmap[t.b].push_back(i);
		vtmap[t.c].push_back(i);
	}

	return tN;
}
