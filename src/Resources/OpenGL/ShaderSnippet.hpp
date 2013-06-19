#ifndef SHADER_SNIPPET_HPP
#define SHADER_SNIPPET_HPP

#include <string>

class ShaderSnippet
{
	public:
		ShaderSnippet();
		ShaderSnippet(const std::string& fields, const std::string& methods, const std::string& mainBodyCode);
};

#endif
