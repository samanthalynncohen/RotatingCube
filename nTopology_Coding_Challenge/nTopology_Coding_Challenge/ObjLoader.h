#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace glm;

class ObjLoader
{
public:
	ObjLoader(void);
	~ObjLoader(void);
	void load(const char * filePath);
	bool loadFromFile(const char * filePath, vector<vec3> & vertices, vector<vec3> & normals, vector<vec3> & colors, vector<vec2> & textures);
	void loadBuffers(vector<vec3> vertices, vector<vec3> normals, vector<vec3> colors, vector<vec2> textures);
	void rotateTexture();
	void initFBO(unsigned int width, unsigned int height);//GLuint textureId);
	void generateDepthTexture(unsigned int width, unsigned int height);
	void generateColorTexture(unsigned int width, unsigned int height);
	unsigned int texture_color;
	GLuint fbo;
private:
	vector<vec3> vertices, normals, colors;
	vector<vec2> textures;
	//unsigned int FBO;                   //framebuffer object
		       
		unsigned int texture_depth;			
		std::vector<GLenum> drawbuffer;     //add texture attachements
};

