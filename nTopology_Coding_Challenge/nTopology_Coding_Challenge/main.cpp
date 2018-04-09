#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include <iostream>
#include <ctime>
#include "Camera.h"
#include "Mouse.h"
#include "ObjLoader.h"
#include "ShaderUtil.h"

using namespace std;
using namespace glm;

const char * filePath = "C:/Users/Samantha/Documents/nTopology_Coding_Challenge/nTopology_Coding_Challenge/ObjFiles/cube.obj";
GLuint shaderProgram;
Camera camera;
Mouse mouse;
ObjLoader objLoader;
ShaderUtil shaderUtil;

void drawScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.3, 0.3, 1.0);
	glUseProgram(shaderProgram);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glutSwapBuffers();
}

void closeCallback()
{
  std::cout << "GLUT:\t Finished" << std::endl;
  glutLeaveMainLoop();
}

void updateScreen()
{
	mat4 rotation = camera.getViewMatrix();
	GLint rotationLocation = glGetUniformLocation(shaderProgram, "rotation");
	glProgramUniformMatrix4fv(shaderProgram, rotationLocation, 1, GL_FALSE, &rotation[0][0]);
	glutPostRedisplay();
}

void handleMouseClick(int button, int state, int x, int y)
{
	mouse.click(button, state);
}

void handleMouseMove(int x, int y)
{
	if (mouse.move(x,y))
	{
		camera.update(mouse.getPositionDelta(), mouse.getSensitivity());
		updateScreen();
	}
}

void onTimerCb(int value)
{
   glutTimerFunc(100, onTimerCb, 0);
}

void initGls(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Window");
	
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutDisplayFunc(drawScreen);
	glutMotionFunc(handleMouseMove);
	glutMouseFunc(handleMouseClick);
	//glutTimerFunc(100, onTimerCb, 0);
	glutCloseFunc(closeCallback);

	glewInit();

	if (glewIsSupported("GL_VERSION_4_3"))
	{
		cout << "Glew Version 4.3 is supported" << endl;
	}
	else
	{
		cout << "Glew Version 4.3 is not supported" << endl;
	}

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv)
{
	initGls(argc, argv);
	shaderProgram = shaderUtil.initShaderProgram("vertexShader.glsl",
                                         "fragmentShader.glsl");
	shaderUtil.loadLights();
	objLoader.load(filePath);
	updateScreen();
	glutMainLoop();
	glDeleteProgram(shaderProgram);
	return 0;
}