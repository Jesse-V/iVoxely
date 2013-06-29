
#include "Game.hpp"
#include "Modeling/Mesh/PlyParser.hpp"
#include "Modeling/DataBuffers/NormalBuffer.hpp"
#include "Modeling/DataBuffers/SampledBuffers/TextureBuffer.hpp"
#include "Modeling/DataBuffers/SampledBuffers/CoordinateMapReader.hpp"
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
    auto mesh = PlyParser::getMesh("Resources/Meshes/cube.ply");
    std::vector<std::shared_ptr<OptionalDataBuffer>> buffers = {
        std::make_shared<NormalBuffer>(NormalBuffer::calcNormalsMWASER(mesh)),
        std::make_shared<TextureBuffer>(
            "Resources/Textures/test_texture.bmp",
            CoordinateMapReader::getMap("Resources/Coordinate Maps/cube.coord")
        )
    };

    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            for (int z = 0; z < 64; z++)
            {
                glm::mat4 modelMatrix = glm::mat4();
                modelMatrix = glm::scale(modelMatrix, glm::vec3(1/8.0f));
                modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, z));

                auto model = std::make_shared<Model>(mesh, buffers);
                model->setModelMatrix(modelMatrix);
                scene_->addModel(model);
            }
        }
    }
}



void Game::addLight()
{
    scene_->setAmbientLight(glm::vec3(0.75, 0.75, 0.75));

    auto light = std::make_shared<Light>(
        scene_->getCamera()->getPosition(), //position
        glm::vec3(1),               //white light
        1.0f                       //power
    );

    scene_->addLight(light);
}



std::shared_ptr<Camera> Game::getCamera(int screenWidth, int screenHeight)
{
    auto camera = std::make_shared<Camera>();
    camera->lookAt(
        glm::vec3(1.57206f,   -0.30442f,  -0.678558f),
        glm::vec3(-0.0587634f, 0.843095f, -0.53454f)
    );
    camera->setPosition(glm::vec3(2.5631f, 1.99537f, 4.18708f));
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

        glutDestroyWindow(glutGetWindow());
        throw std::runtime_error("Game initiation error");
    }

    return *singleton_;
}
