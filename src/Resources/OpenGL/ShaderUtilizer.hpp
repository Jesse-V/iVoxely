#ifndef SHADER_UTILIZER_HPP
#define SHADER_UTILIZER_HPP

#include "ShaderSnippet.hpp"
#include <memory>

class ShaderUtilizer
{
	virtual std::shared_ptr<VertexShaderSnippet> getVertexShaderGLSL() = 0;
	virtual std::shared_ptr<FragmentShaderSnippet> getFragmentShaderGLSL() = 0;
};

#endif
