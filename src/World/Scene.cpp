
#include "Scene.hpp"
#include "Resources/OpenGL/ShaderManager.hpp"
#include "Rendering/DataBuffers/NormalBuffer.hpp"
#include <algorithm>
#include <sstream>
#include <iostream>


Scene::Scene(const std::shared_ptr<Camera>& camera):
	camera(camera)
{}



void Scene::addModel(const std::shared_ptr<RenderableObject>& obj)
{
	sceneObjects.push_back(obj);
}



void Scene::setCamera(const std::shared_ptr<Camera>& sceneCamera)
{
	camera = sceneCamera;
}



void Scene::addLight(const std::shared_ptr<Light>& light)
{
	if (lights.size() > 0)
		throw std::runtime_error("Multiple lights not supported at this time. See issue #9");

	assertRenderableObjectsContainNormalBuffers();
	lights.push_back(light);
}



void Scene::setAmbientLight(const glm::vec3& rgb)
{
	ambientLight = rgb;
}



//render all objects and lights in the scene, as viewed from the camera
void Scene::render()
{
	for_each (sceneObjects.begin(), sceneObjects.end(),
		[&](std::shared_ptr<RenderableObject>& obj)
		{
			if (!obj->hasBeenInitialized())
				obj->initializeAndStore(ShaderManager::createProgram(obj, getVertexShaderGLSL(), getFragmentShaderGLSL(), lights));

			GLuint handle = obj->getProgram()->getHandle();

			glUseProgram(handle);

			camera->sync(handle);
			syncLights(handle);

			obj->render(glGetUniformLocation(handle, "modelMatrix"));
		}
	);
}



void Scene::syncLights(GLuint handle)
{
	GLint ambientLightUniform = glGetUniformLocation(handle, "ambientLight");
	glUniform3f(ambientLightUniform, ambientLight.x, ambientLight.y, ambientLight.z);

	for_each (lights.begin(), lights.end(),
		[&](const std::shared_ptr<Light>& light)
		{
			light->sync(handle);
		}
	);
}



std::shared_ptr<Camera> Scene::getCamera()
{
	return camera;
}



std::shared_ptr<ShaderSnippet> Scene::getVertexShaderGLSL()
{
	return std::make_shared<ShaderSnippet>(
		R".(
			//Scene fields
			attribute vec3 vertex; //position of the vertex
			uniform mat4 viewMatrix, projMatrix; //Camera view and projection matrices
			uniform mat4 modelMatrix; //matrix transforming model mesh into world space

			varying vec3 pos_world;
			varying vec3 eyedirection_camera;
		).",
		R".(
			//Scene methods
			vec4 projectVertex()
			{
				mat4 MVP = projMatrix * viewMatrix * modelMatrix; //Calculate the Model-View-Projection matrix
				return MVP * vec4(vertex, 1); // Convert from model space to clip space
			}
		).",
		R".(
			//Scene main method code
			gl_Position = projectVertex();
			pos_world = (modelMatrix * vec4(vertex, 1)).xyz; //Convert from model space to world space

			vec3 vpos_camera = (viewMatrix * modelMatrix * vec4(vertex, 1)).xyz;
			eyedirection_camera = -vpos_camera;
		)."
	);
}



std::shared_ptr<ShaderSnippet> Scene::getFragmentShaderGLSL()
{
	return std::make_shared<ShaderSnippet>(
		R".(
			//Scene fields
			uniform vec3 ambientLight;
			varying vec3 pos_world;
			varying vec3 eyedirection_camera;
		).",
		R".(
			//Scene methods
		).",
		R".(
			//Scene main method code
		)."
	);
}


void Scene::assertRenderableObjectsContainNormalBuffers()
{
	std::vector<glm::vec3> emptyVec;
	auto normBuffer = std::make_shared<NormalBuffer>(emptyVec);
	for_each (sceneObjects.begin(), sceneObjects.end(),
		[&](std::shared_ptr<RenderableObject>& obj)
		{
			auto optionalBuffers = obj->getAllDataBuffers();
			bool containsNormalBuffer = false;
			for_each (optionalBuffers.begin(), optionalBuffers.end(),
				[&](std::shared_ptr<DataBuffer>& buffer)
				{
					if (typeid(*buffer) == typeid(*normBuffer))
						containsNormalBuffer = true;
				}
			);

			if (!containsNormalBuffer)
			{
				std::stringstream stream;
				stream << "Light added to Scene, yet ";
				stream << typeid(*obj).name();
				stream << " does not contain a NormalBuffer!";

				throw std::runtime_error(stream.str());
			}
		}
	);
}
