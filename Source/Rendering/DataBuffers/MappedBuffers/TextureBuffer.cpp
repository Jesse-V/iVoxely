
#include "TextureBuffer.hpp"


TextureBuffer::TextureBuffer(const std::string imagePath)
{
	loadBMP(imagePath);
}



void TextureBuffer::initialize(GLuint program)
{
	glGenTextures(1, &textureID);
	glGenBuffers(1, &vbo_cube_texcoords);

	attribute_texcoord = glGetAttribLocation(program, "texcoord");
}



void TextureBuffer::store()
{
	storeTexture();
	storeCoordMap();
}


void TextureBuffer::storeTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

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

	glVertexAttribPointer(
		attribute_texcoord, // attribute
		2,                 // number of elements per vertex, here (r,g,b)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
	);
}



void TextureBuffer::enable()
{
	glEnableVertexAttribArray(attribute_texcoord);
}



void TextureBuffer::disable()
{
	//glDisableVertexAttribArray(attribute_texcoord);
}



void TextureBuffer::loadBMP(std::string imagepath)
{
	unsigned char header[54];

	FILE * file = fopen(imagepath.c_str(), "rb");
	if (!file)
		printf("Image could not be opened\n");

	if(fread(header, 1, 54, file) != 54)
		printf("Not a valid BMP file\n");

	if (header[0] != 'B' || header[1] != 'M')
		printf("Not a correct BMP file\n");

	width  = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	int imageSize  = *(int*)&(header[0x22]);
	if (imageSize == 0)
		imageSize = width * height * 3;

	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);
}
