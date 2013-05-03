
#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include "DataBuffer.hpp"
#include "../Mesh.hpp"
#include <memory>

class VertexBuffer: public DataBuffer
{
	public:
		VertexBuffer(const std::shared_ptr<Mesh>& mesh);
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
		std::shared_ptr<Mesh> mesh;
		GLuint vertexBuffer, normalBuffer, meshBuffer;
		GLint vertexAttrib, normalAttrib;
};

#endif
