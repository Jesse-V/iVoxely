
#include "ShaderSnippet.hpp"
#include <iostream>


ShaderSnippet::ShaderSnippet():
	ShaderSnippet("", "", "")
{
	std::cout << "default ShaderSnippet" << std::endl;
}



ShaderSnippet::ShaderSnippet(const std::string& fields, const std::string& methods, const std::string& mainBodyCode):
	fields(fields), methods(methods), mainBodyCode(mainBodyCode)
{
	std::cout << "recorded GLSL snippets" << std::endl;
}



void ShaderSnippet::print()
{
	std::cout << fields << std::endl << methods << std::endl << mainBodyCode << std::endl;
}
