
#ifndef INDEX_BUFFER
#define INDEX_BUFFER

#include "DataBuffer.hpp"
#include "../Triangle.struct"
#include <vector>

class IndexBuffer : public DataBuffer
{
    public:
        IndexBuffer(const std::vector<Triangle>& triangles);
        virtual void initialize(GLuint programHandle);
        virtual void store();
        virtual void enable();
        virtual void disable();
        virtual void draw(GLenum mode);

        virtual std::shared_ptr<ShaderSnippet> getVertexShaderGLSL();
        virtual std::shared_ptr<ShaderSnippet> getFragmentShaderGLSL();

        std::vector<Triangle> getTriangles();

    private:
        std::vector<Triangle> triangles_; //indexes for triangles
        GLuint meshBuffer_;
};

#endif
