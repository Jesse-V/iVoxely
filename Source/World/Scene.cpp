
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

			updateCamera(handle);
			updateLights(handle);

			obj->render(modelMatrixUniform);
		});
}



void Scene::updateCamera(GLuint handle)
{
	GLint viewMatrixUniform = glGetUniformLocation(handle, "viewMatrix");
	GLint projMatrixUniform = glGetUniformLocation(handle, "projMatrix");
	glm::mat4 viewMatrix = glm::lookAt(camera->getPosition(), camera->getLookDirection(), camera->getUpVector());

	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projMatrixUniform, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));
}



//tell the shaders where the light is
void Scene::updateLights(GLuint handle)
{
	GLint ambientLightUniform	= glGetUniformLocation(handle, "ambientLight");
	glUniform3f(ambientLightUniform, ambientLight.x, ambientLight.y, ambientLight.z);

	GLint lightPosUniform = glGetUniformLocation(handle, "lightPosition");
	glUniform3fv(lightPosUniform, 1, glm::value_ptr(lights[0]->getPosition()));

	GLint lightColorUniform = glGetUniformLocation(handle, "lightColor");
	glUniform3fv(lightColorUniform, 1, glm::value_ptr(lights[0]->getColor()));

	GLint lightPowUniform = glGetUniformLocation(handle, "lightPower");
	float power = lights[0]->isEmitting() ? lights[0]->getPower() : 0;
	glUniform1f(lightPowUniform, power);
}



std::shared_ptr<Camera> Scene::getCamera()
{
	return camera;
}
