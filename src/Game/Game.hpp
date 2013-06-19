
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

	private:
		void addModels();
		void addGround();
		void addLight();
		std::shared_ptr<Camera> getCamera(int screenWidth, int screenHeight);
		void moveLight(int deltaTime);
		static void sleep(int milliseconds);

	private:
		std::shared_ptr<Scene> scene;
		std::shared_ptr<Player> player;

		std::shared_ptr<Light> light = std::make_shared<Light>();
		glm::vec3 lightVector = glm::vec3(0.0f, 0.0f, -0.001f);
};

#endif