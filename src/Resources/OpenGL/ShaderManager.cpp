
#include "ShaderManager.hpp"
#include "Program.hpp"
#include <sstream>
#include <algorithm>
#include <iostream>


std::shared_ptr<cs5400::Program> ShaderManager::createProgram(
    const std::shared_ptr<RenderableObject>& obj,
    const std::shared_ptr<ShaderSnippet>& sceneVertexShader,
    const std::shared_ptr<ShaderSnippet>& sceneFragmentShader,
    const std::vector<std::shared_ptr<Light>> lights
)
{
    std::cout << "Creating shaders for " << typeid(*obj).name() << " with " << lights.size() << " light(s)... ";

    auto dataBuffers = obj->getAllDataBuffers();
    auto vertexSnippets = assembleVertexSnippets(sceneVertexShader, dataBuffers, lights);
    auto fragmentSnippets = assembleFragmentSnippets(sceneFragmentShader, dataBuffers, lights);

    std::string vertexShaderStr = buildShader(assembleFields(vertexSnippets), assembleMethods(vertexSnippets), assembleMainBodyCode(vertexSnippets));
    std::string fragmentShaderStr = buildShader(assembleFields(fragmentSnippets), assembleMethods(fragmentSnippets), assembleMainBodyCode(fragmentSnippets));

    auto vertexShader = cs5400::makeVertexShaderStr(vertexShaderStr);
    auto fragmentShader = cs5400::makeFragmentShaderStr(fragmentShaderStr);

    std::cout << "done" << std::endl;
    return cs5400::makeProgram(vertexShader, fragmentShader);
}



std::vector<std::shared_ptr<ShaderSnippet>> ShaderManager::assembleVertexSnippets(
    const std::shared_ptr<ShaderSnippet>& sceneVertexShader,
    const std::vector<std::shared_ptr<DataBuffer>> dataBuffers,
    const std::vector<std::shared_ptr<Light>>& lights
)
{
    std::vector<std::shared_ptr<ShaderSnippet>> vertexSnippets;
    vertexSnippets.push_back(sceneVertexShader);

    for_each (dataBuffers.begin(), dataBuffers.end(),
        [&](const std::shared_ptr<DataBuffer>& buffer)
        {
            vertexSnippets.push_back(buffer->getVertexShaderGLSL());
        }
    );


    for_each (lights.begin(), lights.end(),
        [&](const std::shared_ptr<Light>& light)
        {
            vertexSnippets.push_back(light->getVertexShaderGLSL());
        }
    );

    return vertexSnippets;
}



std::vector<std::shared_ptr<ShaderSnippet>> ShaderManager::assembleFragmentSnippets(
    const std::shared_ptr<ShaderSnippet>& sceneFragmentShader,
    const std::vector<std::shared_ptr<DataBuffer>> dataBuffers,
    const std::vector<std::shared_ptr<Light>>& lights
)
{
    std::vector<std::shared_ptr<ShaderSnippet>> fragmentSnippets;
    fragmentSnippets.push_back(sceneFragmentShader);

    for_each (dataBuffers.begin(), dataBuffers.end(),
        [&](const std::shared_ptr<DataBuffer>& buffer)
        {
            fragmentSnippets.push_back(buffer->getFragmentShaderGLSL());
        }
    );

    for_each (lights.begin(), lights.end(),
        [&](const std::shared_ptr<Light>& light)
        {
            fragmentSnippets.push_back(light->getFragmentShaderGLSL());
        }
    );

    return fragmentSnippets;
}



std::string ShaderManager::assembleFields(
    const std::vector<std::shared_ptr<ShaderSnippet>>& snippets)
{
    std::stringstream stream("");

    for_each (snippets.begin(), snippets.end(),
        [&](const std::shared_ptr<ShaderSnippet>& snippet)
        {
            stream << snippet->getFields();
        }
    );

    return stream.str();
}



std::string ShaderManager::assembleMethods(
    const std::vector<std::shared_ptr<ShaderSnippet>>& snippets)
{
    std::stringstream stream("");

    for_each (snippets.begin(), snippets.end(),
        [&](const std::shared_ptr<ShaderSnippet>& snippet)
        {
            stream << snippet->getMethods();
        }
    );

    return stream.str();
}



std::string ShaderManager::assembleMainBodyCode(
    const std::vector<std::shared_ptr<ShaderSnippet>>& snippets)
{
    std::stringstream stream("");

    for_each (snippets.begin(), snippets.end(),
        [&](const std::shared_ptr<ShaderSnippet>& snippet)
        {
            stream << snippet->getMainBodyCode();
        }
    );

    return stream.str();
}



std::string ShaderManager::buildShader(const std::string& fields,
    const std::string& methods, const std::string& mainBodyCode
)
{
    //return fields + methods + mainBodyCode;
    return R".(
            #version 130
        )."
        + fields
        + "\n"
        + methods
        + R".(
            void main()
            {
        )."
        + mainBodyCode
        + R".(
            }
        ).";
}
