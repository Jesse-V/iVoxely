#pragma GCC diagnostic push //save off current pragma state
#pragma GCC diagnostic ignored "-Wpragmas" //apply custom warning ignore rules
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#pragma GCC diagnostic ignored "-Wexit-time-destructors"
#pragma GCC diagnostic ignored "-Wdisabled-macro-expansion"

#include "Game/Game.hpp"
#include <iostream>
#include <thread>

static std::shared_ptr<Game> game;
static bool readyToUpdate = false;


void updateCallback()
{
	if (readyToUpdate)
	{
		static int oldTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);

		int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		int deltaTime = timeSinceStart - oldTimeSinceStart;
		oldTimeSinceStart = timeSinceStart;

		game->update(deltaTime);
	}
	else
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); //sleep for a bit
}



void renderCallback()
{
	game->render();
	glutPostRedisplay(); //make a call to render again at screen's FPS

	readyToUpdate = true;
}



void keyPressCallback(unsigned char key, int x, int y)
{
	game->onKeyPress(key, x, y);
}



void specialKeyPressCallback(int key, int x, int y)
{
	game->onSpecialKeyPress(key, x, y);
}



void mouseClickCallback(int button, int state, int x, int y)
{
	game->onMouseClick(button, state, x, y);
}



void mouseMotionCallback(int x, int y)
{
	game->onMouseMotion(x, y);
}



void mouseDragCallback(int x, int y)
{
	game->onMouseDrag(x, y);
}



/* Initializes glut. Sets the window size and title to the specified values */
void initializeGlutWindow(int width, int height, const std::string& windowTitle)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(windowTitle.c_str());

	std::cout << "window is " << width << " by " << height << ", a ratio of " << (width / (float)height) << std::endl;
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	initializeGlutWindow(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT), "Final OpenGL Project - Jesse Victors");

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}

	try
	{
		game = std::make_shared<Game>(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));

		glutIdleFunc(updateCallback);
		glutDisplayFunc(renderCallback);

		glutKeyboardFunc(keyPressCallback);
		glutSpecialFunc(specialKeyPressCallback);

		glutMouseFunc(mouseClickCallback);
		glutMotionFunc(mouseDragCallback);
		glutPassiveMotionFunc(mouseMotionCallback);

		std::cout << "Finished assembly. Launching application..." << std::endl;
		glutMainLoop();
	}
	catch (std::exception& e)
	{
		std::cerr << std::endl;
		std::cerr << e.what();
		std::cerr << std::endl;
	}

	return EXIT_SUCCESS;
}

#pragma GCC diagnostic pop //store previous pragma state
