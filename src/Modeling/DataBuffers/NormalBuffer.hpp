
#ifndef NORMAL_BUFFER
#define NORMAL_BUFFER

#include "OptionalDataBuffer.hpp"
#include "Modeling/Mesh/Mesh.hpp"
#include "../Triangle.struct"
#include <vector>
#include <string>

class NormalBuffer : public OptionalDataBuffer
{
    public:
        NormalBuffer(const std::vector<glm::vec3>& normals);
        virtual void initialize(GLuint program);
        virtual void store();
        virtual void enable();
        virtual void disable();

        virtual std::shared_ptr<ShaderSnippet> getVertexShaderGLSL();
        virtual std::shared_ptr<ShaderSnippet> getFragmentShaderGLSL();

        static std::vector<glm::vec3> calcNormalsMWA(
            const std::shared_ptr<Mesh>& mesh
        );
        static std::vector<glm::vec3> calcNormalsMWASER(
            const std::shared_ptr<Mesh>& mesh
        );
        static std::vector<glm::vec3> calcNormalsMWE(
            const std::shared_ptr<Mesh>& mesh
        );

    private:
        static std::vector<glm::vec3> calculateTriangleNormals(
            const std::shared_ptr<Mesh>& mesh,
            std::vector<std::vector<size_t>>& vtmap
        );

    private:
        std::vector<glm::vec3> normals_;

        GLuint normalBuffer_;
        GLint normalAttrib_;
};

#endif
