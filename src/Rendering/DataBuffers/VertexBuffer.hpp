
#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include "DataBuffer.hpp"
#include "glm/glm.hpp"
#include <vector>

class VertexBuffer : public DataBuffer
{
    public:
        VertexBuffer(const std::vector<glm::vec3>& vertices);
        virtual void initialize(GLuint program);
        virtual void store();
        virtual void enable();
        virtual void disable();
        virtual void draw(GLenum mode);

        virtual std::shared_ptr<ShaderSnippet> getVertexShaderGLSL();
        virtual std::shared_ptr<ShaderSnippet> getFragmentShaderGLSL();

        std::vector<glm::vec3> getVertices();

    private:
        void storePoints();
        void enableVertices();

    private:
        std::vector<glm::vec3> vertices_;

        GLuint vertexBuffer_;
        GLint vertexAttrib_;
};

#endif
