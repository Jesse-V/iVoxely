
#ifndef SCENE_HPP
#define SCENE_HPP

#include "Camera.hpp"
#include "Light.hpp"
#include "Resources/OpenGL/Program.hpp"
#include "Rendering/RenderableObject.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

class Scene
{
	public:
		Scene(const std::shared_ptr<Camera>& camera);
		void addModel(const std::shared_ptr<RenderableObject>& obj);
		void setCamera(const std::shared_ptr<Camera>& camera);
		void clear();
		void addLight(const std::shared_ptr<Light>& light);
		void setAmbientLight(const glm::vec3& rgb); // (0,0,0) is total darkness, (1.0,1,0,1,0) is total light
		void render();

		std::shared_ptr<Camera> getCamera();
		std::shared_ptr<cs5400::Program> getProgram();

		virtual std::shared_ptr<ShaderSnippet> getVertexShaderGLSL();
		virtual std::shared_ptr<ShaderSnippet> getFragmentShaderGLSL();

	private:
		void updateCamera(GLuint handle);
		void updateLights(GLuint handle);
		void initialize();

	private:
		std::vector<std::shared_ptr<RenderableObject>> sceneObjects;
		std::vector<std::shared_ptr<Light>> lights;
		std::shared_ptr<Camera> camera;
		glm::vec3 ambientLight;
		bool beenInitialized;
};


#endif
