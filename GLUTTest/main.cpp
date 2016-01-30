#include <GL/glew.h>
#include <gl/freeglut.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>

#include "shaders.hpp"

void centerOnScreen();
GLuint VertexVBOID;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

void render(void);
bool initGL();
void init_VBO();
void init_EBO();
void init_VAO();

void runMainLoop(int val);

//

//  define the window position on screen
int window_x;
int window_y;

//  variables representing the window size
int window_width = 480;
int window_height = 480;

//  variable representing the window title
char *window_title = "Sample OpenGL FreeGlut App";

//-------------------------------------------------------------------------
//  Program Main method.
//-------------------------------------------------------------------------
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("OpenGL");
	centerOnScreen();

	if (!initGL())
	{
		printf("Unable to initialize graphics library!\n");
		return 1;
	}

	// Set the callback functions
	glutDisplayFunc(render);

	//glutTimerFunc(500 / SCREEN_FPS, runMainLoop, 0);

	//  Start GLUT event processing loop
	glutMainLoop();
}

//-------------------------------------------------------------------------
//  Set OpenGL program initial state.
//-------------------------------------------------------------------------
bool initGL()
{
	glewInit();//intit for glew library

	init_VBO();//create vertex buffers and copy to graphics card

	init_EBO();//create element buffer object which refers to indices instead and allows us to reuse vertices.

	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		return false;
	}
	initShaders();//compile join the two shaders,vertex and frament.

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------
//  This function is passed to glutDisplayFunc in order to display 
//  OpenGL contents on the window.
//-------------------------------------------------------------------------
void render()
{
	GLuint shaderProgram = getShaderProgram();
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
		5 * sizeof(float), (void*)(2 * sizeof(float)));
	

	glUseProgram(shaderProgram);

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	glFlush();
	//Update screen
	glutSwapBuffers();
}

void runMainLoop(int val)
{
	glutPostRedisplay();

	glutTimerFunc(500 / SCREEN_FPS, runMainLoop, val);
}

//-------------------------------------------------------------------------
//  This function sets the window x and y coordinates
//  such that the window becomes centered
//-------------------------------------------------------------------------
void centerOnScreen()
{
	window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
	window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
}

//initialize element buffer object. this allows verticies to be displayed by indices(elements). This way you do not have to repeat vertices you may reuse.
void init_EBO() {
	GLuint ebo;
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(elements), elements, GL_STATIC_DRAW);
}

void init_VAO() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);//every time you call glVertexAttribPointer, that information will be stored in that VAO.
}

void init_VBO() {
	//float vertices[] = {
	//	0.0f,  0.5f, // Vertex 1 (X, Y)
	//	0.5f, -0.5f, // Vertex 2 (X, Y)
	//	-0.5f, -0.5f  // Vertex 3 (X, Y)
	//};

	//float vertices[] = {
	//	0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
	//	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
	//	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
	//};

	GLfloat vertices[] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
	};



	glewInit();
	glGenBuffers(1, &VertexVBOID);//generate buffer
	glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);//makes our VertexVBoid buffer the active buffer, now that active we can copy the vertex data to it

	//Notice glBufferData() doesn't refer to the id of our VBO, but instead to the active array buffer.
	//GL_STATIC_DRAW: The vertex data will be uploaded once and drawn many times.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//copy vertices to grapics card

	//printf("%u\n", VertexVBOID);
}