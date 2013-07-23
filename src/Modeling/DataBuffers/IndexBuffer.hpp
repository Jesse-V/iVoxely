
#ifndef INDEX_BUFFER
#define INDEX_BUFFER

#include "DataBuffer.hpp"
#include "Modeling/Mesh/Triangle.struct"
#include "Modeling/Mesh/Quad.struct"
#include <vector>
#include <iostream>

/**
    A IndexBuffer defines a set of Triangles by referencing triplets of points
    in space. This helps to efficiently define a Mesh when vertexes are being
    shared by multiple triangles or quads, so it is recommended to use an
    IndexBuffer in conjunction with a VertexBuffer whenever possible.
    IndexBuffer has no GLSL data GPU-side; it is just used by OpenGL.
**/
class IndexBuffer : public DataBuffer
{
    public:
        IndexBuffer(const std::vector<Triangle>& triangles);
        IndexBuffer(const std::vector<Quad>& quads);
        virtual void initialize(GLuint programHandle);
        virtual void store();
        virtual void enable();
        virtual void disable();
        virtual void draw(GLenum mode);

        virtual SnippetPtr getVertexShaderGLSL();
        virtual SnippetPtr getFragmentShaderGLSL();

        std::vector<Triangle> reinterpretAsTriangles();
        std::vector<Quad> reinterpretAsQuads();

    private:
        std::vector<GLuint> indices;
        GLuint meshBuffer_;
};

#endif
