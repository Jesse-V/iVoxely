#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/* Using the standard output for fprintf */
#include <iostream>
#include <functional>
#include <memory>

#include "Shader.h"
#include "Program.h"

#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>


#include "mathDefs.h"

#define PI_OVER_360 0,0087266

#ifdef _WIN32
	#define WINDOWS 1
#elif _WIN64
	#define WINDOWS 1
#else
	#define WINDOWS 0

#endif


std::shared_ptr<cs5400::Program> program;
std::vector<Triangle> indices;
std::vector<vec3> vertices;



GLuint light_id;


std::vector<vec3> normList;
std::vector<int> polyCount;


//change this to change the ply model loaded

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int cam_x, cam_y;

//model view projection matrix
glm::mat4 mvp;

//camera variables
//up direction of camera -- normalized
glm::vec3 up;
//location of camera
glm::vec3 eye;
//location being looked at
glm::vec3 center;
//unit vector for cam direction
glm::vec3 lookDir;

//model matrix
glm::mat4 model;
glm::mat4 world;
glm::mat4 view;

GLint uniform_mvp;

//mouse state variables
bool mouse1 = false;
bool mouse2 = false;

bool doneOnce = false;

GLuint LightID;


void saveBMPtoGPU(int width, int height, unsigned char* data)
{
	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// Generate mipmaps, by the way.
	glGenerateMipmap(GL_TEXTURE_2D);
}



void loadBMP(std::string imagepath)
{
	unsigned char header[54];

	FILE * file = fopen(imagepath.c_str(), "rb");
	if (!file)
		printf("Image could not be opened\n");

	if(fread(header, 1, 54, file) != 54)
		printf("Not a valid BMP file\n");

	if (header[0] != 'B' || header[1] != 'M')
		printf("Not a correct BMP file\n");

	unsigned int imageSize  = *(int*)&(header[0x22]);
	unsigned int width      = *(int*)&(header[0x12]);
	unsigned int height     = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = width * height * 3;

	unsigned char* data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	saveBMPtoGPU(width, height, data);

	printf("SUCCESS");
}


//create vertices, faces, and vertex normals for the cube
void loadCube()
{
	//front
	vertices.push_back(vec3(-0.1, -0.1, 0.1));
	vertices.push_back(vec3(0.1, -0.1, 0.1));
	vertices.push_back(vec3(0.1, 0.1, 0.1));
	vertices.push_back(vec3(-0.1, 0.1, 0.1));

	//top
	vertices.push_back(vec3(-0.1, 0.1, 0.1));
	vertices.push_back(vec3(0.1, 0.1, 0.1));
	vertices.push_back(vec3(0.1, 0.1, -0.1));
	vertices.push_back(vec3(-0.1, 0.1, -0.1));

	//back
	vertices.push_back(vec3(0.1, -0.1, -0.1));
	vertices.push_back(vec3(-0.1, -0.1, -0.1));
	vertices.push_back(vec3(-0.1, 0.1, -0.1));
	vertices.push_back(vec3(0.1, 0.1, -0.1));

	//bottom
	vertices.push_back(vec3(-0.1, -0.1, -0.1));
	vertices.push_back(vec3(0.1, -0.1, -0.1));
	vertices.push_back(vec3(0.1, -0.1, 0.1));
	vertices.push_back(vec3(-0.1, -0.1, 0.1));

	//left
	vertices.push_back(vec3(-0.1, -0.1, -0.1));
	vertices.push_back(vec3(-0.1, -0.1, 0.1));
	vertices.push_back(vec3(-0.1, 0.1, 0.1));
	vertices.push_back(vec3(-0.1, 0.1, -0.1));

	//right
	vertices.push_back(vec3(0.1, -0.1, 0.1));
	vertices.push_back(vec3(0.1, -0.1, -0.1));
	vertices.push_back(vec3(0.1, 0.1, -0.1));
	vertices.push_back(vec3(0.1, 0.1, 0.1));


	/////////
	//Indices
	/////////

	//front
	indices.push_back(Triangle(0,1,2));
	indices.push_back(Triangle(2,3,0));
	normList.push_back(vec3(0,0,1.0));
	normList.push_back(vec3(0,0,1.0));
	normList.push_back(vec3(0,0,1.0));
	normList.push_back(vec3(0,0,1.0));

	//top
	indices.push_back(Triangle(4,5,6));
	indices.push_back(Triangle(6,7,4));
	normList.push_back(vec3(0,1.0,0));
	normList.push_back(vec3(0,1.0,0));
	normList.push_back(vec3(0,1.0,0));
	normList.push_back(vec3(0,1.0,0));


	//back
	indices.push_back(Triangle(10,9,8));
	indices.push_back(Triangle(8,11,10));
	normList.push_back(vec3(0,0,-1.0));
	normList.push_back(vec3(0,0,-1.0));
	normList.push_back(vec3(0,0,-1.0));
	normList.push_back(vec3(0,0,-1.0));

	//bottom
	indices.push_back(Triangle(12,13,14));
	indices.push_back(Triangle(14,15,12));
	normList.push_back(vec3(0,-1.0,0));
	normList.push_back(vec3(0,-1.0,0));
	normList.push_back(vec3(0,-1.0,0));
	normList.push_back(vec3(0,-1.0,0));

	//left
	indices.push_back(Triangle(16,17,18));
	indices.push_back(Triangle(18,19,16));
	normList.push_back(vec3(-1.0,0,0));
	normList.push_back(vec3(-1.0,0,0));
	normList.push_back(vec3(-1.0,0,0));
	normList.push_back(vec3(-1.0,0,0));

	//right
	indices.push_back(Triangle(20,21,22));
	indices.push_back(Triangle(22,23,20));
	normList.push_back(vec3(1.0,0,0));
	normList.push_back(vec3(1.0,0,0));
	normList.push_back(vec3(1.0,0,0));
	normList.push_back(vec3(1.0,0,0));

	std::cout << "NORMLIST: " << normList.size() << std::endl;
	std::cout << "indices: " << indices.size() << std::endl;
	std::cout << "verts: " << vertices.size() << std::endl;

}



void saveTriangles()
{
	GLuint vbo_triangle;
	glGenBuffers(1, &vbo_triangle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
}



void saveVertices()
{
	//init coord3d
	auto attribute_coord3d = glGetAttribLocation(program->getHandle(), "coord3d");
	glEnableVertexAttribArray(attribute_coord3d);

  /* Describe our vertices array to OpenGL (it can't guess its format automatically) */
	glVertexAttribPointer(
		attribute_coord3d, // attribute
		3,                 // number of elements per vertex, here (x,y,z)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0 // vec3er to the C array
	);
}



void saveNormals()
{
	GLuint normalBuffer;
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normList.size() * sizeof(vec3), &normList[0], GL_STATIC_DRAW);

	auto attribute_v_normal = glGetAttribLocation(program->getHandle(), "v_normal");
	glEnableVertexAttribArray(attribute_v_normal);
	glVertexAttribPointer(
		attribute_v_normal, // attribute
		3,                 // number of elements per vertex, here (r,g,b)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
	);
}



void saveCubeTexture()
{
	//create UV coordinates for cube
	GLfloat cube_texcoords[2 * 4 * 6] = {
		// front
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
	};

	for (int i = 1; i < 6; i++)
		memcpy (&cube_texcoords[i*4*2], &cube_texcoords[0], 2*4*sizeof(GLfloat));

	GLuint vbo_cube_texcoords;
	glGenBuffers(1, &vbo_cube_texcoords);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_texcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_texcoords), cube_texcoords, GL_STATIC_DRAW);

	auto attribute_texcoord = glGetAttribLocation(program->getHandle(), "texcoord");
	glEnableVertexAttribArray(attribute_texcoord);
	glVertexAttribPointer(
		attribute_texcoord, // attribute
		2,                 // number of elements per vertex, here (r,g,b)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
	);
}



void load_resources()
{
	//enable backface culling
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glCullFace(GL_FRONT);

	glUseProgram(program->getHandle());

	saveTriangles();
	saveVertices();
	saveNormals();
	saveCubeTexture();

	// Get a handle for our "LightPosition" uniform
	LightID = glGetUniformLocation(program->getHandle(), "LightPosition_worldspace");

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_INDEX_ARRAY );

	loadBMP("texture.bmp");

	glIndexPointer( GL_UNSIGNED_INT, 0, &indices[0] );
}



void onDisplay()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); //Clear the background as black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glm::vec3 light = glm::vec3(-1.0f, 1.0f, 1.0f);

	auto uniform_mvp = glGetUniformLocation(program->getHandle(), "mvp");
	glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

	auto uniform_m = glGetUniformLocation(program->getHandle(), "m");
	glUniformMatrix4fv(uniform_m, 1, GL_FALSE, glm::value_ptr(model));

	auto uniform_v = glGetUniformLocation(program->getHandle(), "v");
	glUniformMatrix4fv(uniform_v, 1, GL_FALSE, glm::value_ptr(view));

	glm::vec3 lightPos = glm::vec3(4,4,3);
	glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

	glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT, &indices[0]);

	glutSwapBuffers();
}



void keyboardInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		//zoom in
		case 'w':
			eye = eye + lookDir * 0.02f;
			center = center + lookDir * 0.02f;
			break;

		//zoom out
		case 's':
			eye = eye - lookDir * 0.02f;
			center = center - lookDir * 0.02f;
			break;

		case 'd':
			//pan right
			eye = eye + (glm::vec3(1.0,0.0,0.0))*0.02f;
			center = center + (glm::vec3(1.0,0.0,0.0))*0.02f;
			break;

		case 'a':
			//pan left
			eye = eye - (glm::vec3(1.0,0.0,0.0))*0.02f;
			center = center - (glm::vec3(1.0,0.0,0.0))*0.02f;
			break;

		case 'q':
			//pan up
			eye = eye + (glm::vec3(0.0,1.0,0.0))*0.02f;
			center = center + (glm::vec3(0.0,1.0,0.0))*0.02f;
			break;

		case 'e':
			//pan down
			eye = eye - (glm::vec3(0.0,1.0,0.0))*0.02f;
			center = center - (glm::vec3(0.0,1.0,0.0))*0.02f;
			break;

		//return to default front view
		case 'f':
			model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,-1.0));
			world = glm::mat4(1.0f);

			eye = glm::vec3(0.0,0.0,0.0);
			center = glm::vec3(0.0,0.0,-1.0);
			up = glm::vec3(0.0,1.0,0.0);

			view = glm::lookAt(eye, center, up);
			break;

	}

	glm::vec3 tempVec = center - eye;
	lookDir = getUnitVector(tempVec);
}



void idle(int value)
{
	glm::mat4 projection = glm::perspective(45.0f, 1.0f*(SCREEN_WIDTH/SCREEN_HEIGHT), 0.1f, 255.0f);
	view = glm::lookAt(eye, center, glm::vec3(0.0,1.0,0.0));

	mvp = projection * view * world * model;
	glutTimerFunc(1, idle,value);
	glutPostRedisplay();
}



void processPassive(int x, int y)
{
	//pitch and roll
	if(mouse1)
	{
		glm::vec3 axis_y(0.0, 1.0, 0.0);
		glm::vec3 axis_x(1.0, 0.0, 0.0);

		float angleX = 0.0f;
		float angleY = 0.0f;

		if(doneOnce)
			angleX = (cam_x - x)/5.0f;
		cam_x = x;

		if(doneOnce)
			angleY = (cam_y - y)/5.0f;
		cam_y = y;

		model = glm::rotate(model, angleX, axis_y);
		model = glm::rotate(model, angleY, axis_x);

		doneOnce = true;
	}

	//yaw
	if(mouse2)
	{
		glm::vec3 axis_z(0.0, 0.0, 1.0);

		float angleX = 0.0f;
		float angleY = 0.0f;

		if(doneOnce)
			angleX = (cam_x - x)/5.0f;
		cam_x = x;

		if(doneOnce)
			angleY = (cam_y - y)/5.0f;
		cam_y = y;

		model = glm::rotate(model, angleX, axis_z);
		model = glm::rotate(model, angleY, axis_z);

		doneOnce = true;
	}
}



//set whether right or left mouse button is clicked
void processMouse(int button, int state, int x, int y)
{

	if(button == GLUT_LEFT_BUTTON)
		mouse1 = true;
	else
		mouse1 = false;

	if(button == GLUT_RIGHT_BUTTON)
		mouse2 = true;
	else
		mouse2 = false;
}



//initialize model view world projection matrices
void initializeMatrices()
{
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0,0.0,-1.0));
	world = glm::mat4(1.0f);

	eye = glm::vec3(0.0,0.0,0.0);
	center = glm::vec3(0.0,0.0,-1.0);
	up = glm::vec3(0.0,1.0,0.0);
	view = glm::lookAt(eye, center, up);
	lookDir = getUnitVector(center - eye);

	glm::mat4 projection = glm::perspective(45.0f, 1.0f*(SCREEN_WIDTH/SCREEN_HEIGHT), 0.1f, 255.0f);
	mvp = projection * view * world * model;

	glMatrixMode(GL_PROJECTION);
	gluPerspective(45,	//view angle
		1.0,    //aspect ratio
		10.0,   //near clip
		200.0); //far clip
	glMatrixMode(GL_MODELVIEW);
}



void generateProgram()
{
	std::string vertShader;
	std::string fragShader;
	if(WINDOWS)
	{
		vertShader = "../vertex.glsl";
		fragShader = "../fragment.glsl";
	}
	else if(!WINDOWS)
	{
		vertShader = "vertex.glsl";
		fragShader = "fragment.glsl";
	}

	program = cs5400::make_program
	(
		cs5400::make_vertexShader(vertShader)
		,cs5400::make_fragmentShader(fragShader)
	);
}



int main(int argc, char* argv[])
{
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Lighting");

	loadCube();

	/* Extension wrangler initialising */
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}

	initializeMatrices();

	/* When all init functions runs without errors,
	the program can initialise the resources */
	try
	{
		generateProgram();

		load_resources();

		glutDisplayFunc(onDisplay);
		glutKeyboardFunc(keyboardInput);
		glutMotionFunc(processPassive);
		glutMouseFunc(processMouse);

		glutTimerFunc(5, idle,0);
		glutMainLoop();
	}
	catch(std::exception& e)
	{
		std::cerr << e.what();
	}
	return EXIT_SUCCESS;
}
