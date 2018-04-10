#include "ObjLoader.h"

ObjLoader::ObjLoader(void)
{
}


ObjLoader::~ObjLoader(void)
{
}

void ObjLoader::load(const char * filePath)
{
	loadFromFile(filePath, vertices, normals, colors);
	loadBuffers(vertices, normals, colors);
}

bool ObjLoader::loadFromFile(const char * filePath, vector<vec3> & vertices, vector<vec3> & normals, vector<vec3> & colors)
{
	vector<vec3> tempVertices, tempNormals;
	vector<unsigned int> faceVertexIndices, faceNormalIndices;

	FILE * file = fopen(filePath, "r");
	string line;

	if (file == NULL)
	{
		cout << "Could not load file: " << filePath << endl;
		return false;
	}
	else
	{
		while(1)
		{
			char firstString[128];
			if (fscanf(file, "%s", firstString) == EOF)
			{
				break;
			}
			
			if (strcmp(firstString, "v") == 0)
			{
				vec3 vec;
				fscanf(file, "%f %f %f\n", &vec.x, &vec.y, &vec.z);
				tempVertices.push_back(vec);
			}
			else if (strcmp(firstString, "vn") == 0)
			{
				vec3 vec;
				fscanf(file, "%f %f %f\n", &vec.x, &vec.y, &vec.z);
				tempNormals.push_back(vec);
			}
			else if (strcmp(firstString, "f") == 0)
			{
				unsigned int faceVertices[3], faceNormals[3];
				/** Not using textures right now **/
				unsigned int faceTextures[3];
				/**********************************/
				
				fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
					&faceVertices[0], &faceTextures[0], &faceNormals[0], 
					&faceVertices[1], &faceTextures[1], &faceNormals[1], 
					&faceVertices[2], &faceTextures[2], &faceNormals[2]);
				
				faceVertexIndices.push_back(faceVertices[0]);
				faceVertexIndices.push_back(faceVertices[1]);
				faceVertexIndices.push_back(faceVertices[2]);
				
				faceNormalIndices.push_back(faceNormals[0]);
				faceNormalIndices.push_back(faceNormals[1]);
				faceNormalIndices.push_back(faceNormals[2]);
			}
		}

		for (unsigned int i = 0; i < faceVertexIndices.size(); i++)
		{
			unsigned int vertexIndex = faceVertexIndices[i];
			vertices.push_back(tempVertices[vertexIndex - 1]);

			unsigned int normalIndex = faceNormalIndices[i];
			normals.push_back(tempNormals[normalIndex - 1]);

			colors.push_back(vec3(0.0,0.0,1.0));
		}
	}

	return true;
}

void ObjLoader::loadBuffers(vector<vec3> vertices, vector<vec3> normals, vector<vec3> colors)
{
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

	/** Setting up normal buffer **/
	unsigned int nbo;
	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);

	/** Setting up normal buffer **/
	unsigned int cbo;
	glGenBuffers(1, &cbo);
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec3), &colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
}
