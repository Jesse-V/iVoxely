
#include "main.hpp"
#include "Game/Game.hpp"
#include <thread>
#include <sstream>

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

            Game::getInstance().update(deltaTime);
        }
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); //sleep for a bit
    }
    catch (std::exception& e)
    {
        std::cerr << "Caught " << typeid(e).name() << " during update: " <<
            e.what() << std::endl;
        std::cerr << "\"And on that bombshell it is time to end. Good night!\"";
        std::cerr << std::endl;
        glutDestroyWindow(glutGetWindow());
    }
}



void renderCallback()
{
    try
    {
        Game::getInstance().render();
        glutPostRedisplay(); //make a call to render again at screen's FPS

        readyToUpdate = true;
    }
    catch (std::exception& e)
    {
        std::cerr << "Caught " << typeid(e).name() << " during render: " <<
            e.what() << std::endl;
        std::cerr << "\"And on that bombshell it is time to end. Good night!\"";
        std::cerr << std::endl;
        glutDestroyWindow(glutGetWindow());
    }
}



void keyPressCallback(unsigned char key, int x, int y)
{
    try
    {
        Game::getInstance().onKeyPress(key, x, y);
    }
    catch (std::exception& e)
    {
        std::cerr << "Caught " << typeid(e).name() << " during key press: " <<
            e.what() << std::endl;
        std::cerr << "\"And on that bombshell it is time to end. Good night!\"";
        std::cerr << std::endl;
        glutDestroyWindow(glutGetWindow());
    }
}



void specialKeyPressCallback(int key, int x, int y)
{
    try
    {
        Game::getInstance().onSpecialKeyPress(key, x, y);
    }
    catch (std::exception& e)
    {
        std::cerr << "Caught " << typeid(e).name()
            << " during special key press: " << e.what() << std::endl;
        std::cerr << "\"And on that bombshell it is time to end. Good night!\"";
        std::cerr << std::endl;
        glutDestroyWindow(glutGetWindow());
    }
}



void mouseClickCallback(int button, int state, int x, int y)
{
    try
    {
        Game::getInstance().onMouseClick(button, state, x, y);
    }
    catch (std::exception& e)
    {
        std::cerr << "Caught " << typeid(e).name() << " during mouse click: " <<
            e.what() << std::endl;
        std::cerr << "\"And on that bombshell it is time to end. Good night!\"";
        std::cerr << std::endl;
        glutDestroyWindow(glutGetWindow());
    }
}



void mouseMotionCallback(int x, int y)
{
    try
    {
        Game::getInstance().onMouseMotion(x, y);
    }
    catch (std::exception& e)
    {
        std::cerr << "Caught " << typeid(e).name() << " during mouse motion: "
            << e.what() << std::endl;
        std::cerr << "\"And on that bombshell it is time to end. Good night!\"";
        std::cerr << std::endl;
        glutDestroyWindow(glutGetWindow());
    }
}



void mouseDragCallback(int x, int y)
{
    try
    {
        Game::getInstance().onMouseDrag(x, y);
    }
    catch (std::exception& e)
    {
        std::cerr << "Caught " << typeid(e).name() << " during mouse drag: " <<
            e.what() << std::endl;
        std::cerr << "\"And on that bombshell it is time to end. Good night!\"";
        std::cerr << std::endl;
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



void createGlContext()
{
    GLenum glew_status = glewInit();
    if (glew_status == GLEW_OK)
        std::cout << "Successfully created GL context." << std::endl;
    else
    {
        std::stringstream errorStream("");
        errorStream << "glewInit() error. Failed to create GL context.";
        errorStream << std::endl;
        errorStream << glewGetErrorString(glew_status);
        throw std::runtime_error(errorStream.str());
    }

    std::cout << "<GL context>" << std::endl;
    std::cout << "Vendor:   " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version:  " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL:     " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "</GL context>" << std::endl;
}



void assertSystemRequirements()
{
    std::stringstream stream("");
    stream << glGetString(GL_SHADING_LANGUAGE_VERSION);

    float version;
    stream >> version;

    const float MIN_GLSL = 1.30f;

    if (version < MIN_GLSL)
        throw std::runtime_error("Your driver/GPU does not support OpenGL 3.0");
    else
        std::cout << "GLSL v" << MIN_GLSL << " required, have " << version <<
            ", so passed system requirements." << std::endl;
}



void assignCallbacks()
{
    glutIdleFunc(updateCallback);
    glutDisplayFunc(renderCallback);

    glutKeyboardFunc(keyPressCallback);
    glutSpecialFunc(specialKeyPressCallback);

    glutMouseFunc(mouseClickCallback);
    glutMotionFunc(mouseDragCallback);
    glutPassiveMotionFunc(mouseMotionCallback);
}



int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    initializeGlutWindow(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT), "iVoxely");

    try
    {
        createGlContext();
        assertSystemRequirements();
        assignCallbacks();

        std::cout << "Finished Glut and window initialization." << std::endl;

        Game::getInstance(); //calls Game's constructor, sets up everything...
        glutMainLoop();
    }
    catch (std::exception& e)
    {
        std::cerr << std::endl << "Caught " << typeid(e).name() <<
            " during glut setup: " << e.what() << std::endl;

        std::cerr << "\"And on that bombshell it is time to end. Good night!\"";
        std::cerr << std::endl;
        glutDestroyWindow(glutGetWindow());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
