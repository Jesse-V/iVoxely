
#include "Player.hpp"
#include "World/Camera.hpp"


Player::Player(std::shared_ptr<Scene> scene):
    scene_(scene)
{}



void Player::onKeyPress(unsigned char key)
{
    std::shared_ptr<Camera> camera = scene_->getCamera();

    switch(key)
    {
        case 'a':
            camera->moveRight(-TRANSLATION_SPEED);
            break;

        case 'd':
            camera->moveRight(TRANSLATION_SPEED);
            break;

        case 's':
            camera->moveForward(-TRANSLATION_SPEED);
            break;

        case 'w':
            camera->moveForward(TRANSLATION_SPEED);
            break;

        case 'q':
            camera->moveUp(-TRANSLATION_SPEED);
            break;

        case 'e':
            camera->moveUp(TRANSLATION_SPEED);
            break;
    }

    scene_->getLights()[0]->setPosition(scene_->getCamera()->getPosition());
}



void Player::onSpecialKeyPress(int key)
{
    std::shared_ptr<Camera> camera = scene_->getCamera();

    switch(key)
    {
        case GLUT_KEY_UP:
            camera->constrainedPitch(ROTATION_SPEED);
            break;

        case GLUT_KEY_DOWN:
            camera->constrainedPitch(-ROTATION_SPEED);
            break;

        case GLUT_KEY_LEFT:
            camera->yaw(ROTATION_SPEED);
            break;

        case GLUT_KEY_RIGHT:
            camera->yaw(-ROTATION_SPEED);
            break;

        case GLUT_KEY_PAGE_UP:
            camera->constrainedRoll(-ROTATION_SPEED);
            break;

        case GLUT_KEY_PAGE_DOWN:
            camera->constrainedRoll(ROTATION_SPEED);
            break;
    }
}



void Player::onMouseClick(int button, int state, int x, int y)
{

}



void Player::onMouseMotion(int x, int y)
{

}



void Player::onMouseDrag(int x, int y)
{

}
