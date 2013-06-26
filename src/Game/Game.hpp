
#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "World/Scene.hpp"
#include <memory>

class Game
{
    public:
        Game(int screenWidth, int screenHeight);
        void update(int deltaTime);
        void render();

        void onKeyPress(unsigned char key, int, int);
        void onSpecialKeyPress(int key, int x , int y);
        void onMouseClick(int button, int state, int x, int y);
        void onMouseMotion(int x, int y);
        void onMouseDrag(int x, int y);

        static Game& getInstance();

    private:
        void addModels();
        void addGround();
        void addLight();
        std::shared_ptr<Camera> getCamera(int screenWidth, int screenHeight);
        void moveLight(int deltaTime);
        static void sleep(int milliseconds);

    private:
        static Game* singleton_;

        std::shared_ptr<Scene> scene_;
        std::shared_ptr<Player> player_;

        glm::vec3 lightVector_ = glm::vec3(0.0f, 0.0f, -0.001f);
};

#endif
