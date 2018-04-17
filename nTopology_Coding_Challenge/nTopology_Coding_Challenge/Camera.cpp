#include "Camera.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265359f

using namespace glm;

Camera::Camera(void)
{
	fov = 45.0f;

	width = 800.0f;
	height = 600.0f;

	eye = vec3(100.0f, 100.0f, 100.0f);
	target = vec3(0.0f, 0.0f, 0.0f);
	up = vec3(0.0f, 1.0f, 0.0f);

	direction = normalize(eye - target);
	right = normalize(cross(up, direction));
	cameraUp = normalize(cross(direction, right));

	view = lookAt(eye, target, up);
	projection = perspective(radians(fov), width / height, 0.1f, 200.0f); 
	model = mat4(1.0f);//rotate(model, radians(0.0f), vec3(1.0f, 0.0f, 0.0f)); 
	
	yaw = -90.0f;
	pitch =  0.0f;
	roll = 0.0f;
	radius = length(eye-target);
}


Camera::~Camera(void)
{
}

mat4 Camera::getModel()
{
	return model;
}

mat4 Camera::getView()
{
	return view;
}

mat4 Camera::getProjection()
{
	return projection;
}

void Camera::update(vec2 positionDelta, float sensitivity)
{	
	yaw += positionDelta.x * sensitivity;
	pitch += positionDelta.y * sensitivity;

	/*if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}*/

	eye.x = cos(radians(yaw)) * cos(radians(pitch)) * radius;
	eye.y = sin(radians(pitch)) * radius;
	eye.z = sin(radians(yaw)) * cos(radians(pitch)) * radius;

	direction = normalize(eye - target);
	right = normalize(cross(up, direction));
	cameraUp = normalize(cross(direction, right));

	view = lookAt(eye, target, cameraUp);
}

vec3 Camera::screenToWorld(int x, int y, int width, int height)
{
	/*double u = 2.0 * winX / width - 1;
    double v = - 2.0 * winY / height + 1;
    mat4 viewProjectionInverse = inverse(projection * view);

    vec4 world(u,v,1.0f,1.0f); 
	cout << u << ", " << v << ", " << 1.0f << endl;
    return vec3(viewProjectionInverse * world);*/
	return vec3(1.0f);
}
