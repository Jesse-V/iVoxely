
#ifndef SHADER_MANAGER
#define SHADER_MANAGER

#include "Modeling/Model.hpp"
#include "Modeling/DataBuffers/DataBuffer.hpp"
#include "World/Light.hpp"
#include "Program.hpp"
#include <memory>
#include <vector>
#include <GL/glut.h>

class ShaderManager
{
    public:
        static ProgramPtr createProgram(const std::shared_ptr<Model>& obj,
            const SnippetPtr& sceneVertexShader,
            const SnippetPtr& sceneFragmentShader, const LightList& lights
        );

    private:
        static std::vector<SnippetPtr> assembleVertexSnippets(
            const SnippetPtr& sceneVertexShader,
            const BufferList& buffers, const LightList& lights
        );
        static std::string assembleVertexShaderStr(
            const BufferList& buffers, const SnippetPtr& sceneVertexShader,
            const LightList& lights
        );

        static std::vector<SnippetPtr> assembleFragmentSnippets(
            const SnippetPtr& sceneFragmentShader,
            const BufferList& buffers, const LightList& lights
        );
        static std::string assembleFragmentShaderStr(
            const BufferList& buffers, const SnippetPtr& sceneFragmentShader,
            const LightList& lights
        );

        static std::string assembleFields(const SnippetList& snippets);
        static std::string assembleMethods(const SnippetList& snippets);
        static std::string assembleMainBodyCode(const SnippetList& snippets);
        static std::string buildShader(const std::string& fields,
            const std::string& methods, const std::string& mainBodyCode
        );
};

#endif
