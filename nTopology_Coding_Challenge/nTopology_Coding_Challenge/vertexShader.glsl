#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec3 in_color;

out vec3 fragment_position;
out vec3 fragment_color;
out vec3 fragment_normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(in_position, 1.0f);
	fragment_position = vec3(model * vec4(in_position, 1.0f));
	fragment_color = in_color;
	fragment_normal = in_normal;
}