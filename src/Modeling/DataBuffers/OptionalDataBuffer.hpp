
#ifndef OPTIONAL_DATA_BUFFER
#define OPTIONAL_DATA_BUFFER

#include "DataBuffer.hpp"

class OptionalDataBuffer : public DataBuffer
{
    public:
        virtual void draw(GLenum mode) {} //OptionalDataBuffers cannot be drawn
};

#endif
