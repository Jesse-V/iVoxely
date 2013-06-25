
#include "ShaderSnippet.hpp"
#include <iostream>


ShaderSnippet::ShaderSnippet():
    ShaderSnippet("", "", "")
{}



ShaderSnippet::ShaderSnippet(const std::string& fields,
    const std::string& methods, const std::string& mainBodyCode):
    fields(fields), methods(methods), mainBodyCode(mainBodyCode)
{}



std::string ShaderSnippet::getFields()
{
    return fields;
}



std::string ShaderSnippet::getMethods()
{
    return methods;
}



std::string ShaderSnippet::getMainBodyCode()
{
    return mainBodyCode;
}
