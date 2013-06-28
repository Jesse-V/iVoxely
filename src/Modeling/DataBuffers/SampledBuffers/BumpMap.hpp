
#ifndef BUMP_MAP
#define BUMP_MAP

#include "SampledBuffer.hpp"

class BumpMap : public SampledBuffer
{
    public:
        BumpMap(const std::string& mapPath,
                const std::vector<GLfloat>& coordinateMap);

        virtual void initialize(GLuint programHandle);
        virtual void enable();
        virtual void disable();

        virtual void store();

        virtual std::shared_ptr<ShaderSnippet> getVertexShaderGLSL();
        virtual std::shared_ptr<ShaderSnippet> getFragmentShaderGLSL();
};

#endif
