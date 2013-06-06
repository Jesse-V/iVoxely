
#ifndef INDEX_BUFFER
#define INDEX_BUFFER

#include "DataBuffer.hpp"
#include "../Triangle.struct"
#include <vector>

class IndexBuffer: public DataBuffer
{
	public:
		IndexBuffer(const std::vector<Triangle>& triangles);
		virtual void initialize(GLuint program);
		virtual void store();
		virtual void enable();
		virtual void disable();
		virtual bool draw(GLenum mode);

	private:
		std::vector<Triangle> triangles; // indexes for triangles, {(0,1,2), (3,4,5)}
		GLuint meshBuffer;
};

#endif
