
#ifndef MESH
#define MESH

#include "Modeling/DataBuffers/IndexBuffer.hpp"
#include "Modeling/DataBuffers/VertexBuffer.hpp"
#include "Modeling/Triangle.struct"

class Mesh : public DataBuffer
{
    public:
        Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer);
        Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer,
             const std::shared_ptr<IndexBuffer>& indexBuffer
        );

        virtual void initialize(GLuint program);
        virtual void store();
        virtual void enable();
        virtual void disable();
        virtual void draw(GLenum mode);

        virtual std::shared_ptr<ShaderSnippet> getVertexShaderGLSL();
        virtual std::shared_ptr<ShaderSnippet> getFragmentShaderGLSL();

        std::vector<glm::vec3> getVertices();
        std::vector<Triangle> getTriangles();

    private:
        void generateDefaultTriangles();

    private:
        std::shared_ptr<VertexBuffer> vertexBuffer_;
        std::shared_ptr<IndexBuffer> indexBuffer_;

        std::vector<Triangle> defaultTriangles_;
};

#endif
