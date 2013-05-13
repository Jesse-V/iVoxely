
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
		std::vector<glm::vec3> vertices; // Complete set of vertices in the mesh
		std::vector<glm::vec3> normals; // vertex normals
		std::vector<Triangle> triangles; // indexes for triangles, {(0,1,2), (3,4,5)}
};

#endif
