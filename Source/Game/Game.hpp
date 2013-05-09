
#ifndef GAME_HPP
#define GAME_HPP

#include "World/Scene.hpp"
#include <memory>

class Game
{
	public:
		const float TRANSLATION_SPEED = 0.0078125f;
		const float ROTATION_SPEED = 0.5f;

	public:
		Game(int screenWidth, int screenHeight);
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
		void addCamera();
		void moveLight();
		static void sleep(int milliseconds);

	private:
		Scene scene;
		std::shared_ptr<Light> light = std::make_shared<Light>();
		int screenWidth, screenHeight;
		glm::vec3 lightVector = glm::vec3(0.0f, 0.0f, -0.015f);
};

#endif
