
#include "MappedBuffer.hpp"
#include <iostream>


MappedBuffer::MappedBuffer(const std::string& imagePath)
{
	std::string status = loadBMP("dfsd");
	if (status != "success")
		std::cout << "Error loading \"" + imagePath + "\" image: " << status << std::endl;
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



std::string MappedBuffer::loadBMP(const std::string& imagePath)
{
	unsigned char header[54];

	FILE * file = fopen(imagePath.c_str(), "rb"); //read binary .bmp file
	if (!file)
		return "File could not be opened";

	if(fread(header, 1, 54, file) != 54)
		return "Invalid BMP file";

	if (header[0] != 'B' || header[1] != 'M')
		return "Not a correct BMP file";

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
	return "success";
}



void MappedBuffer::deleteBufferFromRAM()
{
	if (isValid)
	{
		delete [] data;
		isValid = false;
	}
}
