
#ifndef PLAYER
#define PLAYER

#include "World/Scene.hpp"
#include <memory>

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
