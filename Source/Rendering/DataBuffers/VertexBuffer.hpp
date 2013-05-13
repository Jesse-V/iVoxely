
#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include "DataBuffer.hpp"
#include "../Triangle.struct"
#include <vector>

class VertexBuffer: public DataBuffer
{
	public:
		VertexBuffer(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles, const std::vector<glm::vec3>& normals);
		virtual void initialize(GLuint program);
		virtual void store();
		virtual void enable();
		virtual void disable();

	private:
		void storePoints();
		void storeNormals();
		void storeMesh();

		void enableVertices();
		void enableNormals();

	private:
		std::vector<glm::vec3> vertices; // Complete set of vertices
		std::vector<Triangle> triangles; // indexes for triangles, {(0,1,2), (3,4,5)}
		std::vector<glm::vec3> normals; // vertex normals

		GLuint vertexBuffer, normalBuffer, meshBuffer;
		GLint vertexAttrib, normalAttrib;
};

#endif
