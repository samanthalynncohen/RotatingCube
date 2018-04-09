#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include <iostream>
#include <ctime>
#include "ShaderUtil.h"
#include "ObjLoader.h"
#include "Camera.h"
#include "Mouse.h"

using namespace std;
using namespace glm;
int num = 0;

GLuint shaderProgram;
const char * filePath = "C:/Users/Samantha/Documents/nTopology_Coding_Challenge/nTopology_Coding_Challenge/ObjFiles/cube.obj";
Camera camera;
Mouse mouse;
int mouseButton, mouseState, keyState = 0, lastX = 0, lastY = 0;

void loadShaders()
{
	glEnable(GL_DEPTH_TEST);

	ShaderUtil shaderUtil;
	shaderProgram = shaderUtil.initShaderProgram("vertexShader.glsl",
                                         "fragmentShader.glsl");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void loadObjBuffers()
{
	ObjLoader objLoader;

	vector<vec3> vertices;
	vector<vec3> normals;
	vector<vec3> colors;

	objLoader.load(filePath, vertices, normals, colors);
	
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	/** Setting up vertex buffer **/
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);

	/** Setting up color buffer **/
	unsigned int cbo;
	glGenBuffers(1, &cbo);
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec3), &colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

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

void drawRotation()
{
	mat4 rotation = camera.getViewMatrix();
	GLint rotationLocation = glGetUniformLocation(shaderProgram, "rotation");
	glProgramUniformMatrix4fv(shaderProgram, rotationLocation, 1, GL_FALSE, &rotation[0][0]);
	glutPostRedisplay();
}

void handleMouseClick(int button, int state, int x, int y)
{
	mouse.setButton(button);
	mouse.setState(state);
}

void handleMouseMove(int x, int y)
{
	bool mouseMoved = mouse.move(x,y);

	if (mouseMoved)
	{
		camera.update(mouse.getPositionDelta(), mouse.getSensitivity());
		drawRotation();
	}
}

void onTimerCb(int value)
{
   glutTimerFunc(100, onTimerCb, 0);
}

void init(int argc, char **argv)
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
}

int main(int argc, char **argv)
{
	init(argc, argv);
	loadShaders();
	loadObjBuffers();
	drawRotation();
	glutMainLoop();
	glDeleteProgram(shaderProgram);
	return 0;
}