
#ifndef BUMP_MAP
#define BUMP_MAP

#include "../DataBuffer.hpp"

class BumpMap: public DataBuffer
{
	public:
		BumpMap();
		virtual void initialize(GLuint program);
		virtual void store();
		virtual void enable();
		virtual void disable();
};

#endif
