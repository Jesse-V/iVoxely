
#ifndef OPTIONAL_DATA_BUFFER
#define OPTIONAL_DATA_BUFFER

#include "DataBuffer.hpp"

class OptionalDataBuffer : public DataBuffer
{
    public:
        virtual void draw(GLenum mode) {} //OptionalDataBuffers cannot be drawn

        virtual void derp() = 0;
};

#endif
