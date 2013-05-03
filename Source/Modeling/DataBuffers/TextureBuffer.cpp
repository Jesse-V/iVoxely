
#include "TextureBuffer.hpp"


void TextureBuffer::initialize(GLuint program)
{
	glGenBuffers(1, &buffer);
	glGenTextures(1, &texture);
	textureAttrib = glGetAttribLocation(program, "textureCoord");
	vTexCoord = glGetAttribLocation(program, "vTexCoord");
	glUniform1i(glGetUniformLocation(program, "texture"), 0);
}



void TextureBuffer::store()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);
}



void TextureBuffer::enable()
{
	glEnableVertexAttribArray(vTexCoord);
	glBindTexture(GL_TEXTURE_2D, texture);
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glActiveTexture(GL_TEXTURE0);
}



void TextureBuffer::disable()
{
	glDisableVertexAttribArray(textureAttrib);
	glDisableVertexAttribArray(vTexCoord);
}
