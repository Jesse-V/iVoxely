
#include "ShaderManager.hpp"
#include "Program.hpp"
#include <sstream>
#include <algorithm>
#include <thread>
#include <iostream>


ProgramPtr ShaderManager::createProgram(
    const std::shared_ptr<Model>& model, const SnippetPtr& sceneVertexShader,
    const SnippetPtr& sceneFragmentShader, const LightList& lights
)
{
    if (model->getProgram()) //if the model already has it, then use it!
        return model->getProgram();

    std::cout << "Creating vertex and fragment shaders for Model"
        << " with " << lights.size() << " light(s)... ";

    auto buffers = model->getOptionalDataBuffers();
    auto vertexShaderStr = assembleVertexShaderStr(buffers,
                                              sceneVertexShader, lights);
    auto fragmentShaderStr = assembleFragmentShaderStr(buffers,
                                              sceneFragmentShader, lights);

    std::cout << "done" << std::endl;
    return cs5400::makeProgram(
        cs5400::makeVertexShaderStr(vertexShaderStr),
        cs5400::makeFragmentShaderStr(fragmentShaderStr)
    );
}



std::string ShaderManager::assembleVertexShaderStr(
    const BufferList& buffers, const SnippetPtr& sceneVertexShader,
    const LightList& lights
)
{
    auto vertexSnippets = assembleVertexSnippets(sceneVertexShader,
                                                 buffers, lights);
    return buildShader(
        assembleFields(vertexSnippets),
        assembleMethods(vertexSnippets),
        assembleMainBodyCode(vertexSnippets)
    );
}



std::string ShaderManager::assembleFragmentShaderStr(
    const BufferList& buffers, const SnippetPtr& sceneFragmentShader,
    const LightList& lights
)
{
    auto fragmentSnippets = assembleFragmentSnippets(sceneFragmentShader,
                                                     buffers, lights);
    return buildShader(
        assembleFields(fragmentSnippets),
        assembleMethods(fragmentSnippets),
        assembleMainBodyCode(fragmentSnippets)
    );
}



std::vector<SnippetPtr> ShaderManager::assembleVertexSnippets(
    const SnippetPtr& sceneVertexShader, const BufferList& buffers,
    const LightList& lights
)
{
    std::vector<SnippetPtr> vertexSnippets;
    vertexSnippets.reserve(1 + buffers.size() + lights.size());
    vertexSnippets.push_back(sceneVertexShader);

    for_each (buffers.begin(), buffers.end(),
        [&](const std::shared_ptr<OptionalDataBuffer>& buffer)
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



std::vector<SnippetPtr> ShaderManager::assembleFragmentSnippets(
    const SnippetPtr& sceneFragmentShader, const BufferList& buffers,
    const LightList& lights
)
{
    std::vector<SnippetPtr> fragmentSnippets;
    fragmentSnippets.reserve(1 + buffers.size() + lights.size());
    fragmentSnippets.push_back(sceneFragmentShader);

    for_each (buffers.begin(), buffers.end(),
        [&](const std::shared_ptr<OptionalDataBuffer>& buffer)
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



std::string ShaderManager::assembleFields(const SnippetList& snippets)
{
    std::stringstream stream("");

    for_each (snippets.begin(), snippets.end(),
        [&](const SnippetPtr& snippet)
        {
            stream << snippet->getFields();
        }
    );

    return stream.str();
}



std::string ShaderManager::assembleMethods(const SnippetList& snippets)
{
    std::stringstream stream("");

    for_each (snippets.begin(), snippets.end(),
        [&](const SnippetPtr& snippet)
        {
            stream << snippet->getMethods();
        }
    );

    return stream.str();
}



std::string ShaderManager::assembleMainBodyCode(const SnippetList& snippets)
{
    std::stringstream stream("");

    for_each (snippets.begin(), snippets.end(),
        [&](const SnippetPtr& snippet)
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
