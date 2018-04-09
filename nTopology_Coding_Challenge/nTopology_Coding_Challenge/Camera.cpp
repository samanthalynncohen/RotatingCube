#include "Camera.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265359f

using namespace glm;

Camera::Camera(void)
{
	viewMatrix = mat4(1.0f);
}


Camera::~Camera(void)
{
}

mat4 Camera::getViewMatrix()
{
	return viewMatrix;
}

void Camera::update(vec2 positionDelta, float sensitivity)
{
	yaw += positionDelta.x * sensitivity;
	pitch += positionDelta.y * sensitivity;

	mat4 tempRoll = mat4(1.0f);
	mat4 tempPitch = mat4(1.0f);
	mat4 tempYaw = mat4(1.0f);

	tempRoll = rotate(tempRoll, roll, vec3(0.0f, 0.0f, 1.0f));
	tempPitch = rotate(tempPitch, pitch, vec3(1.0f, 0.0f, 0.0f));
	tempYaw = rotate(tempYaw, yaw, vec3(0.0f, 1.0f, 0.0f));

	mat4 rotation = tempRoll * tempPitch * tempYaw;

	viewMatrix = rotation;
}
