#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec3 in_normal;

out vec3 fragment_position;
out vec3 fragment_color;
out vec3 fragment_normal;

uniform mat4 rotation;

void main()
{
	gl_Position = rotation * vec4(in_position, 1.0f);
	fragment_position = in_position;//should multiply by model
	fragment_color = in_color;
	fragment_normal = in_normal;
}