#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include <math.h>
#include <iostream>

using namespace glm;
using namespace std;

class Camera
{
public:
	Camera(void);
	~Camera(void);
	mat4 getModel();
	mat4 getView();
	mat4 getProjection();
	void update(vec2 positionDelta, float sensitivity);
	vec3 screenToWorld(int x, int y, int width, int height);
private:
	mat4 view, projection, model;
	float pitch, yaw, roll, fov, width, height, radius;
	vec3 eye, target, direction, up, right, cameraUp;
};

