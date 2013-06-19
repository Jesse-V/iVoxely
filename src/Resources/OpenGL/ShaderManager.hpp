#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include "Rendering/RenderableObject.hpp"
#include "World/Light.hpp"
#include <memory>
#include <vector>
//#include <GL/glew.h>
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
		static std::vector<ShaderSnippet> assembleVertexSnippets(
			const std::shared_ptr<RenderableObject>& obj,
			const std::shared_ptr<ShaderSnippet>& sceneVertexShader,
			const std::vector<std::shared_ptr<Light>> lights
		);
		static std::vector<ShaderSnippet> assembleFragmentSnippets(
			const std::shared_ptr<RenderableObject>& obj,
			const std::shared_ptr<ShaderSnippet>& sceneFragmentShader,
			const std::vector<std::shared_ptr<Light>> lights
		);

		static std::string assembleFields(std::vector<ShaderSnippet> fields);
		static std::string assembleMethods();
		static std::string assembleMainBodyCode();
		static std::string buildShader(const std::string& fields, const std::string& methods, const std::string& mainBodyCode);

		//assembleFields
	//assembleMethods
	//assembleMainBodyCode
	//assemble
};

#endif
