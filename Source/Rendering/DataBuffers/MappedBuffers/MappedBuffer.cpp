
#include "MappedBuffer.hpp"


MappedBuffer::MappedBuffer(const std::string& imagePath)
{
	loadBMP(imagePath);
}



MappedBuffer::~MappedBuffer()
{
	deleteBufferFromRAM();
}



void MappedBuffer::store()
{
	storeImage();
	storeCoordMap();

	deleteBufferFromRAM();
}



void MappedBuffer::loadBMP(const std::string& imagePath)
{
	unsigned char header[54];

	FILE * file = fopen(imagePath.c_str(), "rb"); //read binary .bmp file
	if (!file)
		printf("Image could not be opened\n");

	if(fread(header, 1, 54, file) != 54)
		printf("Not a valid BMP file\n");

	if (header[0] != 'B' || header[1] != 'M')
		printf("Not a correct BMP file\n");

	imgWidth  = *(int*)&(header[0x12]);
	imgHeight = *(int*)&(header[0x16]);

	int imageSize  = *(int*)&(header[0x22]);
	if (imageSize == 0)
		imageSize = imgWidth * imgHeight * 3;

	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, (unsigned long)imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	isValid = true;
}



void MappedBuffer::deleteBufferFromRAM()
{
	if (isValid)
	{
		delete [] data;
		isValid = false;
	}
}
