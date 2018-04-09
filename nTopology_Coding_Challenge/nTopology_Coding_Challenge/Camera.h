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
	mat4 getViewMatrix();
	void update(vec2 positionDelta, float sensitivity);
private:
	mat4 viewMatrix;
	float roll, pitch, yaw;
};

