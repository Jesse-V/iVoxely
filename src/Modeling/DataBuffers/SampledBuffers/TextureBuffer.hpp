
#ifndef TEXTURE_BUFFER
#define TEXTURE_BUFFER

#include "SampledBuffer.hpp"

class TextureBuffer : public SampledBuffer
{
    public:
        TextureBuffer(const std::string& imagePath,
                      const std::vector<GLfloat>& coordinateMap);

        virtual void initialize(GLuint programHandle);
        virtual void enable();
        virtual void disable();

        virtual void store();

        virtual SnippetPtr getVertexShaderGLSL();
        virtual SnippetPtr getFragmentShaderGLSL();

    private:
        GLint attribute_texcoord_;
};

#endif
