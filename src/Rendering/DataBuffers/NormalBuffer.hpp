
#ifndef NORMAL_BUFFER
#define NORMAL_BUFFER

#include "DataBuffer.hpp"
#include "../Triangle.struct"
#include <vector>
#include <string>

class NormalBuffer: public DataBuffer
{
    public:
        NormalBuffer(const std::vector<glm::vec3>& normals);
        virtual void initialize(GLuint program);
        virtual void store();
        virtual void enable();
        virtual void disable();
        virtual bool draw(GLenum mode);

        virtual std::shared_ptr<ShaderSnippet> getVertexShaderGLSL();
        virtual std::shared_ptr<ShaderSnippet> getFragmentShaderGLSL();

        static std::vector<glm::vec3> calcNormalsMWA(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles);
        static std::vector<glm::vec3> calcNormalsMWASER(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles);
        static std::vector<glm::vec3> calcNormalsMWE(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles);

    private:
        static std::vector<glm::vec3> calculateTriangleNormals(const std::vector<glm::vec3>& vertices, const std::vector<Triangle>& triangles, std::vector<std::vector<size_t>>& vtmap);

    private:
        std::vector<glm::vec3> normals;

        GLuint normalBuffer;
        GLint normalAttrib;
};

#endif
