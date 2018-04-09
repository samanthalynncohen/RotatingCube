#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include <iostream>

using namespace std;
using namespace glm;

class ShaderUtil
{
public:
	ShaderUtil(void);
	~ShaderUtil(void);
	string loadShader(char *filename);
	GLuint initShader(GLenum type, string source);
	GLuint initShaderProgram(char* vertexShaderName, char* fragmentShaderName);
	void loadLights();
private:
	GLuint shaderProgram;
};

