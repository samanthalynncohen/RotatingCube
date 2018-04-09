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

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);

	if (link_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << endl;
       return 0;
	}

	return program;
}
