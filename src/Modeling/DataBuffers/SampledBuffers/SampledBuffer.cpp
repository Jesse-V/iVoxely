
#include "SampledBuffer.hpp"
#include <stdexcept>
#include <iostream>


SampledBuffer::SampledBuffer(
    const std::string& imagePath,
    const std::vector<GLfloat>& coordinateMap):
    coordinateMap_(coordinateMap)
{
    loadBMP(imagePath);
}



SampledBuffer::~SampledBuffer()
{
    deleteBufferFromRAM();
}



void SampledBuffer::initialize(GLuint programHandle)
{
    glGenBuffers(1, &vbo_coords_);
}



void SampledBuffer::store()
{
    storeImage();
    storeCoordMap();
}



//ideas: http://stackoverflow.com/questions/4983532/what-are-the-texture-coordinates-for-a-cube-in-opengl
void SampledBuffer::storeImage()
{
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth_, imgHeight_, 0, GL_BGR, GL_UNSIGNED_BYTE, data_);

    // When MAGnifying the image (no bigger mipmap available),
    // use LINEAR filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // When MINifying the image, use a LINEAR blend of two mipmaps,
    // each filtered LINEARLY too
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // Generate mipmaps, by the way.
    glGenerateMipmap(GL_TEXTURE_2D);
}



void SampledBuffer::storeCoordMap()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo_coords_);
    glBufferData(GL_ARRAY_BUFFER, coordinateMap_.size() * sizeof(GLfloat),
                 coordinateMap_.data(), GL_STATIC_DRAW);
}



void SampledBuffer::loadBMP(const std::string& imagePath)
{
    std::cout << "Loading image file from " << imagePath << "... ";
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
    std::cout << "done" << std::endl;
}



void SampledBuffer::deleteBufferFromRAM()
{
    if (isValid_)
    {
        delete [] data_;
        isValid_ = false;
    }
}
