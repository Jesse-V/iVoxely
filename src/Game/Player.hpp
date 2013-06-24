
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "World/Scene.hpp"
#include <memory>

class Player
{
    public:
        const float TRANSLATION_SPEED = 0.0078125f;
        const float ROTATION_SPEED = 0.5f;

    public:
        Player(std::shared_ptr<Scene> scene);

        void onKeyPress(unsigned char key);
        void onSpecialKeyPress(int key);
        void onMouseClick(int button, int state, int x, int y);
        void onMouseMotion(int x, int y);
        void onMouseDrag(int x, int y);

    private:
        std::shared_ptr<Scene> scene;
};

#endif
