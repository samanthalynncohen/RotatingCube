#version 430 core
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec3 vertex_color;
layout(location = 3) in vec2 vertex_texture_coord;

out vec3 fragment_position;
out vec3 fragment_color;
out vec3 fragment_normal;
out vec2 fragment_texture_coord;
out highp vec2 uv;
out vec2 fragment_texture_offset;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec2 textureOffset;

void main()
{
	gl_Position = projection * view * model * vec4(vertex_position, 1.0f);
	fragment_position = vec3(model * vec4(vertex_position, 1.0f));
	fragment_color = vertex_color;
	fragment_normal = vertex_normal;
	fragment_texture_coord = vertex_texture_coord;
	uv = vertex_texture_coord;
	fragment_texture_offset = textureOffset;
}