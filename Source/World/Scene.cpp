
#include "Scene.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <algorithm>


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
			GLuint handle = obj->getProgram()->getHandle();
			GLint modelMatrixUniform = glGetUniformLocation(handle, "matrixModel");

			glUseProgram(handle);

			passCameraMatrix(handle);
			passLightPosition(handle);

			obj->render(modelMatrixUniform);
		});
}



void Scene::passCameraMatrix(GLuint handle)
{
	GLint viewMatrixUniform = glGetUniformLocation(handle, "viewMatrix");
	GLint projMatrixUniform = glGetUniformLocation(handle, "projMatrix");
	glm::mat4 viewMatrix = glm::lookAt(camera->getPosition(), camera->getLookDirection(), camera->getUpVector());

	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projMatrixUniform, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));
}



//tell the shaders where the light is
void Scene::passLightPosition(GLuint handle)
{
	glm::vec3 lightPos = lights[0]->getPosition(); //todo: support for multiple lights
	GLint lightPosUniform	= glGetUniformLocation(handle, "worldLightPos");
	GLint ambientLightUniform	= glGetUniformLocation(handle, "ambientLight");

	glUniform3f(lightPosUniform, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(ambientLightUniform, ambientLight.x, ambientLight.y, ambientLight.z);
}



std::shared_ptr<Camera> Scene::getCamera()
{
	return camera;
}
