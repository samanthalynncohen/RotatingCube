#version 430 core

in vec3 fragment_position;
in vec3 fragment_color;
in vec3 fragment_normal;
in vec2 fragment_texture_coord;
in vec2 fragment_texture_offset;
in highp vec2 uv;

out vec3 color;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform sampler2D textureFile;

void main(void)
{
	vec3 norm = normalize(fragment_normal);
	vec3 lightDir = normalize(lightPosition - fragment_position);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
    vec3 ambient = ambientStrength * lightColor;

	color = /*(ambient + diffuse) * */vec3(texture(textureFile, fragment_texture_coord + fragment_texture_offset));//fragment_color;//*/
	//color.r = fragment_texture_coord.x;
	//color.g = fragment_texture_coord.y;

	//color.x = uv.x;//vec3(texture(textureFile, fragment_texture_coord)).x;
	//color.y = uv.y;//vec3(texture(textureFile, fragment_texture_coord)).y;
	//color.z = 0;
}