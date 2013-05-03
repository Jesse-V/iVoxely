
#include <list>
#include <cmath>
#include "Mesh.hpp"


// Calculate the normals for a given mesh using the
// "Mean Weighted by Angle" (MWA) algorithm as seen in the paper
// "A Comparison of Algorithms for Vertex Normal Computation"
void Mesh::calcNormalsMWA()
{
	// keep track of which triangles a given vertex is part of
	std::vector<std::vector<size_t>> vtmap;
	vtmap.resize(vertices.size());

	// calculate triangle normals
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

	normals.clear();

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
			float alpha = asin(sinalpha);

			normal += alpha * tN[tlist[k]];
		}

		normals.push_back(glm::normalize(normal));
	}
}


// Calculate the normals for a given mesh using the
// "Mean Weighted by Angle" (MWASEL) algorithm as seen in the paper
// "A Comparison of Algorithms for Vertex Normal Computation"
void Mesh::calcNormalsMWASEL()
{
	// keep track of which triangles a given vertex is part of
	std::vector<std::vector<size_t>> vtmap;
	vtmap.resize(vertices.size());

	// calculate triangle normals
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

	normals.clear();

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
}


// Calculate the normals for a given mesh using the
// "Mean Weighted Equally" (MWE) algorithm (Naive approach)
void Mesh::calcNormalsMWE()
{
	// keep track of which triangles a given vertex is part of
	std::vector<std::vector<size_t>> vtmap;
	vtmap.resize(vertices.size());

	// calculate triangle normals
	std::vector<glm::vec3> tN;
	for (size_t i = 0; i < triangles.size(); i++)
	{
		const Triangle& t = triangles[i];
		const glm::vec3& a = vertices[t.a];
		const glm::vec3& b = vertices[t.b];
		const glm::vec3& c = vertices[t.c];
		tN.push_back(glm::cross(b-a, c-a));

		vtmap[t.a].push_back(i);
		vtmap[t.b].push_back(i);
		vtmap[t.c].push_back(i);
	}

	normals.clear();

	// Now calculate the vertex normals
	for (size_t i = 0; i < vertices.size(); i++)
	{
		const std::vector<size_t>& tlist = vtmap[i];

		glm::vec3 normal(0.0f, 0.0f, 0.0f);

		for (size_t k = 0; k < tlist.size(); k++)
			normal += tN[tlist[k]];

		normals.push_back(glm::normalize(normal));
	}
}
