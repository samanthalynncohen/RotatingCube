#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

out vec3 fragment_color;

uniform mat4 rotation;

void main()
{
	gl_Position = rotation * vec4(in_position, 1.0f);
	
	fragment_color = in_color;
}