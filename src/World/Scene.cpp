
#include "Scene.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <algorithm>
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

	for_each (lights.begin(), lights.end(),
		[&](const std::shared_ptr<Light>& light)
		{
			/*std::cout << "hi" << std::endl;
			std::cout.flush();
			GLint lightPosUniform = glGetUniformLocation(handle, "lights[0].position");
			std::cout << lightPosUniform << std::endl;
			std::cout.flush();
			glUniform3fv(lightPosUniform, 1, glm::value_ptr(light->getPosition()));

			GLint lightColorUniform = glGetUniformLocation(handle, "lights[0].color");
			glUniform3fv(lightColorUniform, 1, glm::value_ptr(light->getColor()));

			GLint lightPowUniform = glGetUniformLocation(handle, "lights[0].power");
			float power = light->isEmitting() ? light->getPower() : 0;
			glUniform1f(lightPowUniform, power);*/

			//http://www.opengl.org/discussion_boards/showthread.php/164100-GLSL-multiple-lights
			//http://en.wikibooks.org/wiki/GLSL_Programming/GLUT/Multiple_Lights
			//http://www.geeks3d.com/20091013/shader-library-phong-shader-with-multiple-lights-glsl/
			//http://gamedev.stackexchange.com/questions/53822/variable-number-of-lights-in-a-glsl-shader
			//http://stackoverflow.com/questions/8202173/setting-the-values-of-a-struct-array-from-js-to-glsl
		}
	);
}



std::shared_ptr<Camera> Scene::getCamera()
{
	return camera;
}
