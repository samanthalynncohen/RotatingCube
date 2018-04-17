#include "ObjLoader.h"

ObjLoader::ObjLoader(void)
{
}


ObjLoader::~ObjLoader(void)
{
}

void ObjLoader::load(const char * filePath)
{
	loadFromFile(filePath, vertices, normals, colors, textures);
	loadBuffers(vertices, normals, colors, textures);
	//initFBO(800,600);
}

bool ObjLoader::loadFromFile(const char * filePath, vector<vec3> & vertices, vector<vec3> & normals, vector<vec3> & colors, vector<vec2> & textureCoords)
{
	vector<vec3> tempVertices, tempNormals;
	vector<vec2> tempTextureCoords;
	vector<unsigned int> faceVertexIndices, faceTextureCoordIndices, faceNormalIndices;

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
			else if (strcmp(firstString, "vt") == 0)
			{
				vec2 vec;
				fscanf(file, "%f %f\n", &vec.x, &vec.y);
				tempTextureCoords.push_back(vec);
			}
			else if (strcmp(firstString, "f") == 0)
			{
				unsigned int faceVertices[3], faceNormals[3], faceTextures[3];
				
				fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
					&faceVertices[0], &faceTextures[0], &faceNormals[0], 
					&faceVertices[1], &faceTextures[1], &faceNormals[1], 
					&faceVertices[2], &faceTextures[2], &faceNormals[2]);
				
				faceVertexIndices.push_back(faceVertices[0]);
				faceVertexIndices.push_back(faceVertices[1]);
				faceVertexIndices.push_back(faceVertices[2]);

				faceTextureCoordIndices.push_back(faceTextures[0]);
				faceTextureCoordIndices.push_back(faceTextures[1]);
				faceTextureCoordIndices.push_back(faceTextures[2]);
				
				faceNormalIndices.push_back(faceNormals[0]);
				faceNormalIndices.push_back(faceNormals[1]);
				faceNormalIndices.push_back(faceNormals[2]);
			}
		}

		for (unsigned int i = 0; i < faceVertexIndices.size(); i++)
		{
			unsigned int vertexIndex = faceVertexIndices[i];
			vertices.push_back(tempVertices[vertexIndex - 1]);

			unsigned int textureIndex = faceTextureCoordIndices[i];
			textures.push_back(tempTextureCoords[textureIndex - 1]);

			unsigned int normalIndex = faceNormalIndices[i];
			normals.push_back(tempNormals[normalIndex - 1]);

			colors.push_back(vec3(1.0,1.0,1.0));
		}
	}

	return true;
}

void ObjLoader::loadBuffers(vector<vec3> vertices, vector<vec3> normals, vector<vec3> colors, vector<vec2> textures)
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

	/** Setting up color buffer **/
	unsigned int cbo;
	glGenBuffers(1, &cbo);
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec3), &colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);

	/** Setting up texture buffer **/
	unsigned int tbo;
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(vec2), &textures[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)0);
}

void ObjLoader::generateColorTexture(unsigned int width, unsigned int height)
{
	/*int width2, height2, nrChannels2;
	unsigned char *subTex = stbi_load("./smiley.jpg", &width2, &height2, &nrChannels2, 0);
	glGenTextures(1, &texture_color);
	glBindTexture(GL_TEXTURE_2D, texture_color);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, subTex);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_color, 0); // attach it to the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);*/
}

void ObjLoader::generateDepthTexture(unsigned int width, unsigned int height)
{
	glGenTextures(1, &texture_depth);
	glBindTexture(GL_TEXTURE_2D, texture_depth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexSubImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, texture_depth);
}

void ObjLoader::initFBO(unsigned int width, unsigned int height)
{       
	//GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	generateColorTexture(width, height);
	 //bind textures to pipeline. texture_depth is optional .0 is the mipmap level. 0 is the heightest
	 glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_color, 0);
	 glBindFramebuffer(GL_FRAMEBUFFER, 0);

	 if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	 {
 		std::cout << "Error! FrameBuffer is not complete" << std::endl;
	 }

	 glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void ObjLoader::rotateTexture()
{
	    static float r=0.0;
 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(+0.5, +0.5, 0.0);
    glRotatef(r, 5.0, 10.0, 10.0);
 
    glMatrixMode(GL_MODELVIEW);
    /*glLoadIdentity();
 
    glBegin(GL_QUADS);
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f( 1.0, -1.0, 0.0);
        glVertex3f( 1.0,  1.0, 0.0);
        glVertex3f(-1.0,  1.0, 0.0);
    glEnd();*/
	/*float rotation = 20.0f;
	glPushMatrix(); //Save the current matrix.
	//Change the current matrix.
	glTranslatef(1.5f, 1.5f, 0);
	glRotatef(rotation, 0, 0, 1);

	glBegin(GL_QUADS);
	glTexCoord2d(0,0);//xStart,yStart);
	glVertex2f(-12, -1/2);

	glTexCoord2d(1,0);//xEnd,yStart);
	glVertex2f(1/2, -1/2);

	glTexCoord2d(1,1);//xEnd,yEnd); 
	glVertex2f(1/2, 1/2);

	glTexCoord2d(0,1);//xStart,yEnd);
	glVertex2f(-1/2, 1/2);

	glEnd();

	//Reset the current matrix to the one that was saved.
	glPopMatrix();*/
}
