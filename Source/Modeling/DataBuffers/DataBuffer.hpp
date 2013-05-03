
#ifndef DATA_BUFFER
#define DATA_BUFFER

#include <GL/glew.h>
#include <GL/glut.h>

class DataBuffer
{
	public:
		virtual void initialize(GLuint program) = 0;
		virtual void store() = 0;
		virtual void enable() = 0;
		virtual void disable() = 0;
};

#endif
