
#include "Game.hpp"
#include "Voxels/Cube.hpp"
#include <memory>
#include <thread>
#include <algorithm>
#include <iostream>


Game::Game(int screenWidth, int screenHeight):
    scene_(std::make_shared<Scene>(getCamera(screenWidth, screenHeight))),
    player_(std::make_shared<Player>(scene_)), frameCount_(0)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    reportFPS();
    addModels();
    addLight();

    glutSetCursor(GLUT_CURSOR_NONE); //hides the mouse
}



void Game::reportFPS()
{
    std::thread fpsReporter([&]() {
        while (true)
        {
            sleep(1000);
            std::cout << "FPS: " << frameCount_ << std::endl;
            frameCount_ = 0;
        }
    });

    fpsReporter.detach();
}



void Game::addModels()
{
    addCubes();
}



void Game::addCubes()
{
    static std::mt19937 mersenneTwister; //Mersenne Twister PRNG. WAY better randomness!
    static std::uniform_real_distribution<float> randomFloat(0, 1);

    std::cout << "Currently " << scene_->getModels().size() <<
        " Models in Scene. Adding Cubes... " << std::endl;

    //Chunk::generateCubes(scene_, 0, 0);

    const int MIN = -32;
    const int MAX = 32;

    //player should be 8 blocks tall (vs 2 in Minecraft)
    //chunks are 64*64*64

    for (int x = MIN; x < MAX; x++)
    {
        for (int y = MIN; y < MAX; y++)
        {
            for (int z = 0; z <= 0; z++)
            {
                auto cube = std::make_shared<Cube>(Cube::Type::STONE, x, y, z);
                scene_->addModel(cube);
            }
        }
    }

    std::cout << "... done adding cubes. Scene now has " <<
        scene_->getModels().size() << " Models." << std::endl;

    if (scene_->getModels().size() > 9000)
        std::cout << "It's over 9000!!!" << std::endl;

    if (scene_->getModels().size() > 125 * 125)
        std::cout << "WARNING: likely FPS issues rendering that many cubes!" << std::endl;

    checkGlError();
}



void Game::addLight()
{
    scene_->setAmbientLight(glm::vec3(1));

    auto light1 = std::make_shared<Light>(
        glm::vec3(0),       //position
        glm::vec3(0, 0, 1), //green
        2.0f                //power
    );

    //scene_->addLight(light1);

    auto light2 = std::make_shared<Light>(
        scene_->getCamera()->getPosition(), //position
        glm::vec3(1, 0, 0),                 //red
        2.0f                                //power
    );

    //scene_->addLight(light2);

    checkGlError();
}



std::shared_ptr<Camera> Game::getCamera(int screenWidth, int screenHeight)
{
    auto camera = std::make_shared<Camera>();
    camera->setAspectRatio(screenWidth / (float)screenHeight);
    camera->setPosition(glm::vec3(0, -2, 0.5f));

    camera->lookAt(
        glm::vec3(0, 0, 0.5f),
        glm::vec3(0, 0, 1)
    );

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
    frameCount_++;

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
        std::cout << "... finished creating Game." << std::endl;
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
