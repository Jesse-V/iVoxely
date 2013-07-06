
#ifndef MAPPED_BUFFER
#define MAPPED_BUFFER

#include "../OptionalDataBuffer.hpp"
#include "glm/glm.hpp"
#include <vector>
#include <string>

class SampledBuffer : public OptionalDataBuffer
{
    public:
        SampledBuffer(const std::string& imagePath,
                      const std::vector<GLfloat>& coordinateMap);
        ~SampledBuffer();
        //default copy constructor should be fine

        bool loadBMP(const std::string& imagePath);
        bool loadPNG(const std::string& imagePath);
        void deleteBufferFromRAM();

        virtual void initialize(GLuint handle);
        virtual void store();

    protected:
        void storeImage();
        void storeCoordMap();

    protected:
        int imgWidth_, imgHeight_;
        unsigned char* data_;
        bool isValid_ = false;

        std::vector<GLfloat> coordinateMap_;
        GLuint vbo_coords_;
};

#endif
