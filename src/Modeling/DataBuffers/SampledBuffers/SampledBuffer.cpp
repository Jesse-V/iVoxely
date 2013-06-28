
#include "SampledBuffer.hpp"
#include <stdexcept>
#include <iostream>


SampledBuffer::SampledBuffer(const std::string& imagePath)
{
    loadBMP(imagePath);
}



SampledBuffer::~SampledBuffer()
{
    deleteBufferFromRAM();
}



void SampledBuffer::store()
{
    storeImage();
    storeCoordMap();

    deleteBufferFromRAM();
}



void SampledBuffer::loadBMP(const std::string& imagePath)
{
    unsigned char header[54];

    FILE * file = fopen(imagePath.c_str(), "rb"); //read binary .bmp file
    if (!file)
        throw std::runtime_error("Unable to open image at " + imagePath);

    if(fread(header, 1, 54, file) != 54)
        throw std::runtime_error(imagePath + " is not a valid .bmp image");

    if (header[0] != 'B' || header[1] != 'M')
        throw std::runtime_error(imagePath + " is not a valid .bmp image");

    imgWidth_  = *(int*)&(header[0x12]);
    imgHeight_ = *(int*)&(header[0x16]);

    int imageSize  = *(int*)&(header[0x22]);
    if (imageSize == 0)
        imageSize = imgWidth_ * imgHeight_ * 3;

    data_ = new unsigned char[imageSize];

    // Read the actual data from the file into the buffer
    fread(data_, 1, (unsigned long)imageSize, file);

    //Everything is in memory now, the file can be closed
    fclose(file);

    isValid_ = true;
}



void SampledBuffer::deleteBufferFromRAM()
{
    if (isValid_)
    {
        delete [] data_;
        isValid_ = false;
    }
}
