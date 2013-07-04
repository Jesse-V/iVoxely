#ifndef SHADER_UTILIZER
#define SHADER_UTILIZER

#include "ShaderSnippet.hpp"
#include <memory>
#include <vector>

typedef std::shared_ptr<ShaderSnippet> SnippetPtr;
typedef std::vector<SnippetPtr> SnippetList;

class ShaderUtilizer
{
    public:
        virtual SnippetPtr getVertexShaderGLSL() = 0;
        virtual SnippetPtr getFragmentShaderGLSL() = 0;
};

#endif
