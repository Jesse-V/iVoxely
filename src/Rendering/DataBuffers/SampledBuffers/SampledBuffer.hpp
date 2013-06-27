
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

        virtual void store();

    protected:
        virtual void storeImage() = 0;
        virtual void storeCoordMap() = 0;

    protected:
        int imgWidth_, imgHeight_;
        unsigned char* data_;
        bool isValid_ = false;
};

#endif
