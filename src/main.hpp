
#ifndef MAIN
#define MAIN

#include <iostream>


void updateCallback();

void renderCallback();

void keyPressCallback(unsigned char key, int x, int y);

void specialKeyPressCallback(int key, int x, int y);

void mouseClickCallback(int button, int state, int x, int y);

void mouseMotionCallback(int x, int y);

void mouseDragCallback(int x, int y);

void initializeGlutWindow(int width, int height, const std::string& windowTitle);

void createGlContext();

void assertSystemRequirements();

void assignCallbacks();

#endif
