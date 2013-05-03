
#include "Application.hpp"
#include <iostream>


std::shared_ptr<Application> application; //make_unique is not included in C++11 yet...


void displayCallback()
{
	application->render();
}



void keyCallback(unsigned char key, int x, int y)
{
	application->onKey(key, x, y);
}



void specialKeyCallback(int key, int x, int y)
{
	application->onSpecialKey(key, x, y);
}



/* Initializes glut. Sets the window size and title to the specified values */
void initializeGlutWindow(int width, int height, const std::string& windowTitle)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(windowTitle.c_str());

	std::cout << width << ", " << height << " " << (width / (float)height) << std::endl;
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
		application = std::make_shared<Application>(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));

		glutDisplayFunc(displayCallback);
		glutKeyboardFunc(keyCallback);
		glutSpecialFunc(specialKeyCallback);

		//glutMotionFunc(onMouseMotion);
		//glutMouseFunc(onMouseClick);

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
