
#ifndef INDEX_BUFFER
#define INDEX_BUFFER

#include "DataBuffer.hpp"
#include "../Triangle.struct"
#include <vector>

class IndexBuffer: public DataBuffer
{
    public:
        IndexBuffer(const std::vector<Triangle>& triangles);
        virtual void initialize(GLuint program);
        virtual void store();
        virtual void enable();
        virtual void disable();
        virtual bool draw(GLenum mode);

        virtual std::shared_ptr<ShaderSnippet> getVertexShaderGLSL();
        virtual std::shared_ptr<ShaderSnippet> getFragmentShaderGLSL();

    private:
        std::vector<Triangle> triangles; //indexes for triangles
        GLuint meshBuffer;
};

#endif
