#ifndef SHADER_UTILIZER
#define SHADER_UTILIZER

#include "ShaderSnippet.hpp"
#include <memory>

class ShaderUtilizer
{
    public:
        virtual std::shared_ptr<ShaderSnippet> getVertexShaderGLSL() = 0;
        virtual std::shared_ptr<ShaderSnippet> getFragmentShaderGLSL() = 0;
};

#endif
