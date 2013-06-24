
#include "Player.hpp"
#include "World/Camera.hpp"
#include <iostream>


Player::Player(std::shared_ptr<Scene> scene):
    scene(scene)
{}



void Player::onKeyPress(unsigned char key)
{
    std::shared_ptr<Camera> camera = scene->getCamera();

    switch(key)
    {
        case 'a':
            camera->translateX(-TRANSLATION_SPEED);
            break;

        case 'd':
            camera->translateX(TRANSLATION_SPEED);
            break;

        case 'q':
            camera->translateY(-TRANSLATION_SPEED);
            break;

        case 'e':
            camera->translateY(TRANSLATION_SPEED);
            break;

        case 'w':
            camera->translateZ(-TRANSLATION_SPEED);
            break;

        case 's':
            camera->translateZ(TRANSLATION_SPEED);
            break;
    }

    //std::cout << camera->toString() << std::endl;
}



void Player::onSpecialKeyPress(int key)
{
    std::shared_ptr<Camera> camera = scene->getCamera();

    switch(key)
    {
        case GLUT_KEY_UP:
            camera->pitch(ROTATION_SPEED);
            break;

        case GLUT_KEY_DOWN:
            camera->pitch(-ROTATION_SPEED);
            break;

        case GLUT_KEY_LEFT:
            camera->yaw(ROTATION_SPEED);
            break;

        case GLUT_KEY_RIGHT:
            camera->yaw(-ROTATION_SPEED);
            break;
    }

    //std::cout << camera->toString() << std::endl;
}



void Player::onMouseClick(int button, int state, int x, int y)
{
    std::cout << "Click: " << button << ", " << ", " << state << ", " << x << ", " << y << std::endl;
}



void Player::onMouseMotion(int x, int y)
{
    //std::cout << "Motion: " << x << ", " << y << std::endl;
}



void Player::onMouseDrag(int x, int y)
{
    std::cout << "Drag: " << x << ", " << y << std::endl;
}
