
#ifndef TEXTURE_BUFFER
#define TEXTURE_BUFFER

#include "DataBuffer.hpp"
#include "glm/glm.hpp"

class TextureBuffer: public DataBuffer
{
	public:
		virtual void initialize(GLuint program);
		virtual void store();
		virtual void enable();
		virtual void disable();

	public:
		GLubyte image[64][64][3];
		glm::vec2 tex_coords[36];

	private:
		GLint textureAttrib, vTexCoord;
		GLuint texture, buffer;
};

#endif
