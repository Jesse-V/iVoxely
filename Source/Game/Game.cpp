
#include "Game.hpp"
#include "Models/Ground/Ground.hpp"
#include <thread>


Game::Game(int screenWidth, int screenHeight):
	scene(std::make_shared<Scene>()),
	player(std::make_shared<Player>(scene))
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	addModels();
	addLight();
	addCamera(screenWidth, screenHeight);
}



void Game::addModels()
{
	addGround();
}



void Game::addGround()
{
	Ground ground;
	auto rObj = ground.makeObject();

	glm::mat4 objMatrix = glm::mat4();
	objMatrix = glm::scale(objMatrix, glm::vec3(2, 1, 2));
	objMatrix = glm::translate(objMatrix, glm::vec3(0, -0.15, 0));
	rObj->setModelMatrix(objMatrix);

	scene->addModel(rObj);
}



void Game::addLight()
{
	scene->setAmbientLight(glm::vec3(0.75, 0.75, 0.75));
	light->setPosition(glm::vec3(0.0f, 0.0f, 2.0f));
	scene->addLight(light); //todo: send light color and power to GPU
}



void Game::addCamera(int screenWidth, int screenHeight)
{
	auto camera = std::make_shared<Camera>();
	camera->lookAt(glm::vec3(-0.041535, -0.813947, -0.579453), glm::vec3(-0.0114782, 0.590822, -0.80672));
	camera->setPosition(glm::vec3(0.0318538, 0.331304, 2.59333));
	camera->setAspectRatio(screenWidth / (float)screenHeight);
	scene->setCamera(camera);
}



void Game::update()
{
	moveLight();
}



void Game::render()
{
	glClearColor(.39f, 0.58f, 0.93f, 0.0f);	//nice blue background
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	scene->render();

	glutSwapBuffers();
}



void Game::moveLight()
{
	glm::vec3 lightPos = light->getPosition();

	if (lightPos.z < -2)
		lightVector.z = -lightVector.z;
	else if (lightPos.z > 2)
		lightVector.z = -lightVector.z;

	lightPos += lightVector;
	light->setPosition(lightPos);
}



/*	Causes the current thread to sleep for the specified number of milliseconds */
void Game::sleep(int milliseconds)
{
	std::chrono::milliseconds duration(milliseconds);
	std::this_thread::sleep_for(duration); //forget time.h or windows.h, this is the real way to sleep!
}



void Game::onKeyPress(unsigned char key, int, int)
{
	player->onKeyPress(key);
}



void Game::onSpecialKeyPress(int key, int, int)
{
	player->onSpecialKeyPress(key);
}



void Game::onMouseClick(int button, int state, int x, int y)
{
	player->onMouseClick(button, state, x, y);
}



void Game::onMouseMotion(int x, int y)
{
	player->onMouseMotion(x, y);
}



void Game::onMouseDrag(int x, int y)
{
	player->onMouseDrag(x, y);
}
