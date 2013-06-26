
#ifndef MESH_HPP
#define MESH_HPP

#include "Rendering/DataBuffers/IndexBuffer.hpp"
#include "Rendering/DataBuffers/VertexBuffer.hpp"
#include "Rendering/Triangle.struct"

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
        virtual bool draw(GLenum mode);

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