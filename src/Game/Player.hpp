
#ifndef PLAYER
#define PLAYER

#include "World/Scene.hpp"
#include <memory>

/**
    The Player class handles functions relating to user interaction and movement.
    Its main goal is to represent the user interacting with the Scene.
    For example, one of its basic jobs is to accept and handle mouse and keyboard
    actions and use them to move the Scene's Camera accordingly.
    the Scene's Camera.
**/
class Player
{
    public:
        const float TRANSLATION_SPEED = 0.04f;
        const float ROTATION_SPEED = 1.2f;

    public:
        Player(std::shared_ptr<Scene> scene);

        void onKeyPress(unsigned char key);
        void onSpecialKeyPress(int key);
        void onMouseClick(int button, int state, int x, int y);
        void onMouseMotion(int x, int y);
        void onMouseDrag(int x, int y);

    private:
        std::shared_ptr<Scene> scene_;
};

#endif
