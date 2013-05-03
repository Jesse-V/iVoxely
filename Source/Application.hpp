
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "World/Scene.hpp"
#include <memory>

class Application
{
	public:
		const float TRANSLATION_SPEED = 0.0078125f;
		const float ROTATION_SPEED = 0.5f;

	public:
		Application(int screenWidth, int screenHeight);
		void render();
		void onKey(unsigned char key, int, int);
		void onSpecialKey(int key, int, int);

	private:
		void addModels();
		void addGround();
		void addMandelbrot();
		void addMountains();
		void addFirstMountain();
		void addSecondMountain();
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
