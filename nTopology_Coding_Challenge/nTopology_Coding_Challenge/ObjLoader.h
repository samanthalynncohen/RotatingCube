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
	bool loadFromFile(const char * filePath, vector<vec3> & vertices, vector<vec3> & normals, vector<vec3> & colors);
	void loadBuffers(vector<vec3> vertices, vector<vec3> normals, vector<vec3> colors);
private:
	vector<vec3> vertices;
	vector<vec3> normals;
	vector<vec3> colors;
};

