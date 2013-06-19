#ifndef SHADER_SNIPPET_HPP
#define SHADER_SNIPPET_HPP

#include <string>

class ShaderSnippet
{
	public:
		ShaderSnippet();
		ShaderSnippet(const std::string& fields, const std::string& methods, const std::string& mainBodyCode);

		std::string getFields();
		std::string getMethods();
		std::string getMainBodyCode();

	private:
		std::string fields, methods, mainBodyCode;
};

#endif
