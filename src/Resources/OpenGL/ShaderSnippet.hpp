#ifndef SHADER_SNIPPET_HPP
#define SHADER_SNIPPET_HPP

#include <string>

class ShaderSnippet
{

};

class VertexShaderSnippet: public ShaderSnippet
{
	public:
		VertexShaderSnippet()
		{

		}

		VertexShaderSnippet(const std::string& fields, const std::string& methods, const std::string& mainBodyCode)
		{

		}
};

class FragmentShaderSnippet: public ShaderSnippet
{
	public:
		FragmentShaderSnippet()
		{

		}

		FragmentShaderSnippet(const std::string& fields, const std::string& methods, const std::string& mainBodyCode)
		{

		}
};

#endif
