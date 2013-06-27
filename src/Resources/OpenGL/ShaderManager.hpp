
#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include "Rendering/Model.hpp"
#include "Rendering/DataBuffers/DataBuffer.hpp"
#include "World/Light.hpp"
#include "Program.hpp"
#include <memory>
#include <vector>
#include <GL/glut.h>

class ShaderManager
{
    public:
        static std::shared_ptr<cs5400::Program> createProgram(
            const std::shared_ptr<Model>& obj,
            const std::shared_ptr<ShaderSnippet>& sceneVertexShader,
            const std::shared_ptr<ShaderSnippet>& sceneFragmentShader,
            const std::vector<std::shared_ptr<Light>> lights
        );

    private:
        static std::vector<std::shared_ptr<ShaderSnippet>> assembleVertexSnippets(
            const std::shared_ptr<ShaderSnippet>& sceneVertexShader,
            const std::vector<std::shared_ptr<OptionalDataBuffer>> buffers,
            const std::vector<std::shared_ptr<Light>>& lights
        );
        static std::vector<std::shared_ptr<ShaderSnippet>> assembleFragmentSnippets(
            const std::shared_ptr<ShaderSnippet>& sceneFragmentShader,
            const std::vector<std::shared_ptr<OptionalDataBuffer>> buffers,
            const std::vector<std::shared_ptr<Light>>& lights
        );

        static std::string assembleFields(
            const std::vector<std::shared_ptr<ShaderSnippet>>& snippets
        );
        static std::string assembleMethods(
            const std::vector<std::shared_ptr<ShaderSnippet>>& snippets
        );
        static std::string assembleMainBodyCode(
            const std::vector<std::shared_ptr<ShaderSnippet>>& snippets
        );
        static std::string buildShader(const std::string& fields,
            const std::string& methods, const std::string& mainBodyCode
        );
};

#endif
