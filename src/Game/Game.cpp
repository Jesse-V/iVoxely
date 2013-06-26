
#include "Game.hpp"
#include "Models/Ground/Ground.hpp"
#include <thread>
#include <iostream>


Game::Game(int screenWidth, int screenHeight):
    scene_(std::make_shared<Scene>(getCamera(screenWidth, screenHeight))),
    player_(std::make_shared<Player>(scene_))
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    addModels();
    addLight();

    glutSetCursor(GLUT_CURSOR_NONE); //hides the mouse
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

    scene_->addModel(rObj);
}



void Game::addLight()
{
    scene_->setAmbientLight(glm::vec3(0.75, 0.75, 0.75));

    auto light = std::make_shared<Light>(
        glm::vec3(0.0f, 0.0f, 2.0f), //position
        glm::vec3(1),               //white light
        0.03f                       //power
    );

    scene_->addLight(light);
}



std::shared_ptr<Camera> Game::getCamera(int screenWidth, int screenHeight)
{
    auto camera = std::make_shared<Camera>();

    camera->lookAt(
        glm::vec3(-0.041535, -0.813947, -0.579453),
        glm::vec3(-0.0114782, 0.590822, -0.80672)
    );
    camera->setPosition(glm::vec3(0.0318538, 0.331304, 2.59333));
    camera->setAspectRatio(screenWidth / (float)screenHeight);

    return camera;
}



void Game::update(int deltaTime)
{
    moveLight(deltaTime);
}



void Game::render()
{
    glClearColor(.39f, 0.58f, 0.93f, 0.0f); //nice blue background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene_->render();

    glutSwapBuffers();
}



void Game::moveLight(int deltaTime)
{
    glm::vec3 lightPos = scene_->getLights()[0]->getPosition();

    if (lightPos.z < -2)
        lightVector_.z = -lightVector_.z;
    else if (lightPos.z > 2)
        lightVector_.z = -lightVector_.z;

    lightPos += lightVector_ * (float)deltaTime;
    scene_->getLights()[0]->setPosition(lightPos);
}



/**
 * Causes the current thread to sleep
 * for the specified number of milliseconds
 */
void Game::sleep(int milliseconds)
{
    std::chrono::milliseconds duration(milliseconds);
    std::this_thread::sleep_for(duration); //C++11 way to sleep!
}



void Game::onKeyPress(unsigned char key, int, int)
{
    player_->onKeyPress(key);
}



void Game::onSpecialKeyPress(int key, int, int)
{
    player_->onSpecialKeyPress(key);
}



void Game::onMouseClick(int button, int state, int x, int y)
{
    player_->onMouseClick(button, state, x, y);
}



void Game::onMouseMotion(int x, int y)
{
    player_->onMouseMotion(x, y);
}



void Game::onMouseDrag(int x, int y)
{
    player_->onMouseDrag(x, y);
}



Game* Game::singleton_ = 0;

Game& Game::getInstance()
{
    try
    {
        if (singleton_)
            return *singleton_;

        singleton_ = new Game(
            glutGet(GLUT_SCREEN_WIDTH),
            glutGet(GLUT_SCREEN_HEIGHT)
        );
    }
    catch (std::exception& e)
    {
        std::cerr << std::endl;
        std::cerr << "Caught " << typeid(e).name() <<
            " during Game initiation: " << e.what();
        std::cerr << std::endl;

        glutDestroyWindow(glutGetWindow());
        throw std::runtime_error("Game initiation error");
    }

    return *singleton_;
}
