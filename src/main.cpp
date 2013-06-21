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
	try
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
	catch (std::exception& e)
	{
		std::cerr << "Caught " << typeid(e).name() << " during update: " << e.what() << std::endl;
		glutDestroyWindow(glutGetWindow());
	}
}



void renderCallback()
{
	try
	{
		game->render();
		glutPostRedisplay(); //make a call to render again at screen's FPS

		readyToUpdate = true;
	}
	catch (std::exception& e)
	{
		std::cerr << "Caught " << typeid(e).name() << " during render: " << e.what() << std::endl;
		glutDestroyWindow(glutGetWindow());
	}
}



void keyPressCallback(unsigned char key, int x, int y)
{
	try
	{
		game->onKeyPress(key, x, y);
	}
	catch (std::exception& e)
	{
		std::cerr << "Caught " << typeid(e).name() << " during key press: " << e.what() << std::endl;
		glutDestroyWindow(glutGetWindow());
	}
}



void specialKeyPressCallback(int key, int x, int y)
{
	try
	{
		game->onSpecialKeyPress(key, x, y);
	}
	catch (std::exception& e)
	{
		std::cerr << "Caught " << typeid(e).name() << " during special key press: " << e.what() << std::endl;
		glutDestroyWindow(glutGetWindow());
	}
}



void mouseClickCallback(int button, int state, int x, int y)
{
	try
	{
		game->onMouseClick(button, state, x, y);
	}
	catch (std::exception& e)
	{
		std::cerr << "Caught " << typeid(e).name() << " during mouse click: " << e.what() << std::endl;
		glutDestroyWindow(glutGetWindow());
	}
}



void mouseMotionCallback(int x, int y)
{
	try
	{
		game->onMouseMotion(x, y);
	}
	catch (std::exception& e)
	{
		std::cerr << "Caught " << typeid(e).name() << " during mouse motion: " << e.what() << std::endl;
		glutDestroyWindow(glutGetWindow());
	}
}



void mouseDragCallback(int x, int y)
{
	try
	{
		game->onMouseDrag(x, y);
	}
	catch (std::exception& e)
	{
		std::cerr << "Caught " << typeid(e).name() << " during mouse drag: " << e.what() << std::endl;
		glutDestroyWindow(glutGetWindow());
	}
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
		std::cerr << "Caught " << typeid(e).name() << " during initiation: " << e.what();
		std::cerr << std::endl;

		glutDestroyWindow(glutGetWindow());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

#pragma GCC diagnostic pop //store previous pragma state
