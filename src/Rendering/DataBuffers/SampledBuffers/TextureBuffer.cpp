
#include "TextureBuffer.hpp"


TextureBuffer::TextureBuffer(const std::string& imagePath):
	SampledBuffer(imagePath)
{}



void TextureBuffer::initialize(GLuint program)
{
	glGenTextures(1, &textureID);
	glGenBuffers(1, &vbo_cube_texcoords);

	attribute_texcoord = glGetAttribLocation(program, "texcoord");
}



void TextureBuffer::storeImage()
{
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// Generate mipmaps, by the way.
	glGenerateMipmap(GL_TEXTURE_2D);
}



void TextureBuffer::storeCoordMap()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_texcoords);

	GLfloat map[2 * 4 * 1] = {
		// front
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(map), map, GL_STATIC_DRAW);
	glVertexAttribPointer(attribute_texcoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
}



void TextureBuffer::enable()
{
	glEnableVertexAttribArray(attribute_texcoord);
}



void TextureBuffer::disable()
{
	glDisableVertexAttribArray(attribute_texcoord);
}



std::shared_ptr<VertexShaderSnippet> TextureBuffer::getVertexShaderGLSL()
{
	return std::make_shared<VertexShaderSnippet>();/*
		"
			//TextureBuffer fields
			attribute vec2 texcoord;
			out vec2 UV;
		",
		"
			//TextureBuffer methods
		",
		"
			//TextureBuffer main method code
			UV = texcoord;
		"
	);*/
}



std::shared_ptr<FragmentShaderSnippet> TextureBuffer::getFragmentShaderGLSL()
{
	return std::make_shared<FragmentShaderSnippet>();/*
		"
			//TextureBuffer fields
			in vec2 UV;
		",
		"
			//TextureBuffer methods
		",
		"
			//TextureBuffer main method code
			vec3 textureColor = texture(textureSampler, UV).rgb;
		"
	);*/
}
