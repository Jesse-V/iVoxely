
#include "Game.hpp"
#include "Voxels/Cube.hpp"
#include <memory>
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
    addCubes();
}



void Game::addCubes()
{
    std::cout << "Currently " << scene_->getModels().size() <<
        " Models in Scene. Adding Cubes... " << std::endl;

    const int N = 64;
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
        {
            for (int z = 0; z < N; z++)
            {
                auto cube = std::make_shared<Cube>(Cube::CubeType::DIRT, x, y, z);
                scene_->addModel(cube);
            }
        }
    }

    if (scene_->getModels().size())
        throw std::runtime_error("DERP");

    std::cout << "... done adding cubes. Scene now has " <<
        scene_->getModels().size() << " Models" << std::endl;
}



void Game::addLight()
{
    scene_->setAmbientLight(glm::vec3(0.75, 0.75, 0.75));

    auto light = std::make_shared<Light>(
        scene_->getCamera()->getPosition(), //position
        glm::vec3(1),                       //white light
        1.0f                                //power
    );

    scene_->addLight(light);
}



std::shared_ptr<Camera> Game::getCamera(int screenWidth, int screenHeight)
{
    auto camera = std::make_shared<Camera>();
    camera->lookAt(
        glm::vec3(4.01231f, 1.39741f, 3.46247f),
        glm::vec3(0.655955f, -0.514381f, 0.552359f)
    );
    camera->setPosition(glm::vec3(-0.6769f, -0.604629f, -0.612919f));
    camera->setAspectRatio(screenWidth / (float)screenHeight);

    return camera;
}



void Game::update(int deltaTime)
{

}



void Game::render()
{
    glClearColor(.39f, 0.58f, 0.93f, 0.0f); //nice blue background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene_->render();

    glutSwapBuffers();
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

        std::cout << "Creating Game..." << std::endl;
        singleton_ = new Game(
            glutGet(GLUT_SCREEN_WIDTH),
            glutGet(GLUT_SCREEN_HEIGHT)
        );
        std::cout << "... finished creating Game" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << std::endl;
        std::cerr << "Caught " << typeid(e).name() <<
            " during Game initiation: " << e.what();
        std::cerr << std::endl;

        std::cerr << "\"And on that bombshell it is time to end. Good night!\"";
        std::cerr << std::endl;
        glutDestroyWindow(glutGetWindow());
    }

    return *singleton_;
}
