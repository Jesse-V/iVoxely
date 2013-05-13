
#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include "DataBuffer.hpp"
#include "../Triangle.struct"
#include <vector>

class VertexBuffer: public DataBuffer
{
	public:
		VertexBuffer(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles);
		virtual void initialize(GLuint program);
		virtual void store();
		virtual void enable();
		virtual void disable();

	private:
		void storePoints();
		void storeMesh();
		void enableVertices();

	private:
		std::vector<glm::vec3> vertices; // Complete set of vertices
		std::vector<Triangle> triangles; // indexes for triangles, {(0,1,2), (3,4,5)}

		GLuint vertexBuffer, meshBuffer;
		GLint vertexAttrib;
};

#endif
