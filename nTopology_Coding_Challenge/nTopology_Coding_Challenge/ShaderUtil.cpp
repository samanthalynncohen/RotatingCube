#include "ShaderUtil.h"
#include <fstream>
#include <vector>

ShaderUtil::ShaderUtil(void)
{
}


ShaderUtil::~ShaderUtil(void)
{
}

string ShaderUtil::loadShader(char *filename)
{
	string shaderCode;
	ifstream file(filename, ios::in);

	if (!file.good())
	{
		cout << "Bad file" << endl;
		terminate();
	}

	file.seekg(0,ios::end);
	shaderCode.resize((unsigned int) file.tellg());
	file.seekg(0,ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();

	return shaderCode;
}

GLuint ShaderUtil::initShader(GLenum type, string source)
{
	int compile_result = 0;

	GLuint shader = glCreateShader(type);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader,1,&shader_code_ptr,&shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader,GL_COMPILE_STATUS,&compile_result);

	if (compile_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		cout << "ERROR compiling shader" << std::endl << &shader_log[0] << endl;
        return 0;
	}

	return shader;
}

GLuint ShaderUtil::initShaderProgram(char* vertexShaderName, char* fragmentShaderName)
{
	string vertexShaderCode = loadShader(vertexShaderName);
	string fragmentShaderCode = loadShader(fragmentShaderName);

	GLuint vertexShader = initShader(GL_VERTEX_SHADER, vertexShaderCode);
	GLuint fragmentShader = initShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

	int link_result = 0;

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &link_result);

	if (link_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &info_log_length);
		vector<char> program_log(info_log_length);
		glGetProgramInfoLog(shaderProgram, info_log_length, NULL, &program_log[0]);
		cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << endl;
       return 0;
	}

	return shaderProgram;
}

void ShaderUtil::loadLights()
{
	float ambientStrength = 0.3f;
	GLuint ambientStrengthLocation = glGetUniformLocation(shaderProgram, "ambientStrength");
	glProgramUniform1f(shaderProgram, ambientStrengthLocation, ambientStrength);

	vec3 lightPosition = vec3(5.0f,7.0f,-3.0f);
	GLuint lightPositionLocation = glGetUniformLocation(shaderProgram, "lightPosition");
	glProgramUniform3fv(shaderProgram, lightPositionLocation, 1, &lightPosition[0]);

	vec3 lightColor = vec3(1.0f,1.0f,1.0f);
	GLuint lightColorLocation = glGetUniformLocation(shaderProgram, "lightColor");
	glProgramUniform3fv(shaderProgram, lightColorLocation, 1, &lightColor[0]);
}

void ShaderUtil::loadTexture()
{
	int width, height, nrChannels;
	unsigned char *data = stbi_load("./container.jpg", &width, &height, &nrChannels, 0);
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Could not load texture" << endl;
	}

	stbi_image_free(data);
}

void ShaderUtil::shiftTexture(vec2 textureOffset)
{
	GLuint textureOffsetLocation = glGetUniformLocation(shaderProgram, "textureOffset");
	glProgramUniform2fv(shaderProgram, textureOffsetLocation, 1, &textureOffset[0]);
	glutPostRedisplay();
}

void ShaderUtil::updatePerspective(mat4 projection, mat4 view, mat4 model)
{
	GLuint projectionLocation = glGetUniformLocation(shaderProgram, "projection");
	glProgramUniformMatrix4fv(shaderProgram, projectionLocation, 1, GL_FALSE, &projection[0][0]);

	GLuint viewLocation = glGetUniformLocation(shaderProgram, "view");
	glProgramUniformMatrix4fv(shaderProgram, viewLocation, 1, GL_FALSE, &view[0][0]);

	GLuint modelLocation = glGetUniformLocation(shaderProgram, "model");
	glProgramUniformMatrix4fv(shaderProgram, modelLocation, 1, GL_FALSE, &model[0][0]);
	
	glutPostRedisplay();
}
