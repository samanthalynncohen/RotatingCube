#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>

using namespace std;

class ShaderUtil
{
public:
	ShaderUtil(void);
	~ShaderUtil(void);
	string loadShader(char *filename);
	GLuint initShader(GLenum type, string source);
	GLuint initShaderProgram(char* vertexShaderName, char* fragmentShaderName);
};

