
#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include "Rendering/RenderableObject.hpp"
#include "Rendering/DataBuffers/DataBuffer.hpp"
#include "World/Light.hpp"
#include <memory>
#include <vector>
#include <GL/glut.h>

class ShaderManager
{
	public:
		static GLuint createProgram(
			const std::shared_ptr<RenderableObject>& obj,
			const std::shared_ptr<ShaderSnippet>& sceneVertexShader,
			const std::shared_ptr<ShaderSnippet>& sceneFragmentShader,
			const std::vector<std::shared_ptr<Light>> lights
		);

	private:
		static std::vector<std::shared_ptr<ShaderSnippet>> assembleVertexSnippets(
			const std::shared_ptr<ShaderSnippet>& sceneVertexShader,
			const std::vector<std::shared_ptr<DataBuffer>> dataBuffers,
			const std::vector<std::shared_ptr<Light>>& lights
		);
		static std::vector<std::shared_ptr<ShaderSnippet>> assembleFragmentSnippets(
			const std::shared_ptr<ShaderSnippet>& sceneFragmentShader,
			const std::vector<std::shared_ptr<DataBuffer>> dataBuffers,
			const std::vector<std::shared_ptr<Light>>& lights
		);

		static std::string assembleFields(const std::vector<std::shared_ptr<ShaderSnippet>>& snippets);
		static std::string assembleMethods(const std::vector<std::shared_ptr<ShaderSnippet>>& snippets);
		static std::string assembleMainBodyCode(const std::vector<std::shared_ptr<ShaderSnippet>>& snippets);
		static std::string buildShader(const std::string& fields, const std::string& methods, const std::string& mainBodyCode);
};

#endif
