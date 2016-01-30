#include <iostream>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <vector>
#include "shaders.hpp"

using namespace std;

#define GLchar char
//could of also for gl_Position did this - gl_Position = vec4(position.x, position.y, 0.0, 1.0);
const char *vertexSource = "attribute vec2 position; \
	attribute vec3 color;\
	varying vec3 Color;\
    void main( ) \
    { \
		Color = color;\
        gl_Position = vec4(position, 0.0, 1.0);\
    }";

const char *fragmentSource = "varying vec3 Color;\
	void main( ) \
    { \
        gl_FragColor = vec4(Color, 1.0); \
    }";

GLuint shaderProgram;

GLuint getShaderProgram() {
    return shaderProgram;
}

void initShaders() {
	//--------------------------------------------------------------------------
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint statusV;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &statusV);
	printf("test");

	char bufferV[512];
	glGetShaderInfoLog(vertexShader, 512, NULL, bufferV);//get vertex shader log
	//----------------------------------------------------------------------------
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint statusF;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &statusF);
	printf("test");

	char bufferF[512];
	glGetShaderInfoLog(fragmentShader, 512, NULL, bufferF);//get fragment shader log
	//---------------------------------------------------------------------------------
	//Combine the two shaders into a program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindFragDataLocation(shaderProgram, 0, "outColor");//0 by default and only one output right now so not needed

	glLinkProgram(shaderProgram);

	GLint isLinked = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE) {
		printf("Error occured!\n");
	}
	else {
		printf("Shaders successfully compiled\n");
	}
}