
#ifndef INDEX_BUFFER
#define INDEX_BUFFER

#include "DataBuffer.hpp"

class IndexBuffer: public DataBuffer
{
	public:
		IndexBuffer();
		virtual void initialize(GLuint program);
		virtual void store();
		virtual void enable();
		virtual void disable();
};

#endif
