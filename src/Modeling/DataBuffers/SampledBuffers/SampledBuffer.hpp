
#ifndef MAPPED_BUFFER
#define MAPPED_BUFFER

#include "../OptionalDataBuffer.hpp"
#include "glm/glm.hpp"
#include <string>

class SampledBuffer : public OptionalDataBuffer
{
    public:
        SampledBuffer(const std::string& imagePath);
        ~SampledBuffer();
        //default copy constructor should be fine

        void loadBMP(const std::string& imagePath);
        void deleteBufferFromRAM();

        virtual void initialize(GLuint program);
        virtual void store();

    protected:
        int imgWidth_, imgHeight_;
        unsigned char* data_;
        GLuint vbo_coords_;
        bool isValid_ = false;

    private:
        void storeImage();
        void storeCoordMap();
};

#endif
