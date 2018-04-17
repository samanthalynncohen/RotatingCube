#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include <iostream>
#include <ctime>
#include "Camera.h"
#include "Mouse.h"
#include "ObjLoader.h"
#include "ShaderUtil.h"

using namespace std;
using namespace glm;

const char * filePath = "./ObjFiles/cube.obj";
GLuint shaderProgram;
Camera camera;
Mouse mouse;
ObjLoader objLoader;
ShaderUtil shaderUtil;
bool first = true;

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

void handleMouseClick(int button, int state, int x, int y)
{
	mouse.click(button, state);
}

void handleMouseMove(int x, int y)
{
	if (mouse.changePerspective(x,y))
	{
		camera.update(mouse.getPositionDelta(), mouse.getSensitivity());
		shaderUtil.updatePerspective(camera.getProjection(), 
									camera.getView(),
									camera.getModel());
	}
	else if (mouse.draw(x,y))
	{
		cout << "drawing" << endl;
	}
}

void onTimerCb(int value)
{
	shaderUtil.shiftTexture(vec2(value*0.01f,0.0f));

	glutTimerFunc(100, onTimerCb, ++value % 100);
}

void initGls(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Window");
	
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutDisplayFunc(drawScreen);
	glutMotionFunc(handleMouseMove);
	glutMouseFunc(handleMouseClick);
	glutTimerFunc(100, onTimerCb, 0);
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
	objLoader.load(filePath);
	shaderProgram = shaderUtil.initShaderProgram("vertexShader.glsl",
                                         "fragmentShader.glsl");
	shaderUtil.loadLights();
	shaderUtil.loadTexture();
	shaderUtil.updatePerspective(camera.getProjection(), 
									camera.getView(),
									camera.getModel());
	glutMainLoop();
	glDeleteProgram(shaderProgram);
	return 0;
}
