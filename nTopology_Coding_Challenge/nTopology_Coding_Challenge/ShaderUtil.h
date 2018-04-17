#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\stb\stb_image.h"
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
	void loadTexture();
	void shiftTexture(vec2 textureOffset);
	void updatePerspective(mat4 projection, mat4 view, mat4 model);
private:
	GLuint shaderProgram;
};

