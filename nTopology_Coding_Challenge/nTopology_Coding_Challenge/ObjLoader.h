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
	bool load(const char * filePath, vector<vec3> & vertices, vector<vec3> & normals, vector<vec3> & colors);
};

