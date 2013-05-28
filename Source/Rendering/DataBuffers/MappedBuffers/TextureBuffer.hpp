
#ifndef TEXTURE_BUFFER
#define TEXTURE_BUFFER

#include "../DataBuffer.hpp"
#include "glm/glm.hpp"
#include <string>

class TextureBuffer: public DataBuffer
{
	public:
		TextureBuffer(const std::string imagePath);

		virtual void initialize(GLuint program);
		virtual void store();
		virtual void enable();
		virtual void disable();

		void loadBMP(std::string imagepath);

	private:
		void storeTexture();
		void storeCoordMap();

	private:
		GLuint textureID, vbo_cube_texcoords;
		//GLfloat map;
		GLint attribute_texcoord;
		int width, height;
		unsigned char* data;

	/*public:
		GLubyte image[64][64][3];
		glm::vec2 tex_coords[36];

	private:
		GLint textureAttrib, vTexCoord;
		GLuint texture, buffer;*/
};

#endif
