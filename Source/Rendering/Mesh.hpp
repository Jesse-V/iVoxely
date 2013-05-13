
#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glut.h>
#include <vector>
#include "glm/glm.hpp"


struct Triangle
{
	Triangle(GLuint aa, GLuint bb, GLuint cc)
		: a(aa), b(bb), c(cc)
	{}

	GLuint a, b, c;
};


class Mesh
{
	public:
		// Calculate the normals of the mesh using the
		// Mean Weighted by Angle algorithm
		// This will clear and populate the normals vector
		void calcNormalsMWA();

		// Calculate the normals of the mesh using the
		// Mean Weighted Average By Sine And Edge Reciprocal
		// This will clear and populate the normals vector
		void calcNormalsMWASEL();

		// Naive wait to calculate normals
		void calcNormalsMWE();

		// Complete set of vertices in the mesh
		std::vector<glm::vec3> vertices;

		// vertex normals
		std::vector<glm::vec3> normals;

		// vertex indicies that make up the triangles of this mesh
		// (0,1,2), (3,4,5) ...  are indexes for triangles
		std::vector<Triangle> triangles;
};

#endif
