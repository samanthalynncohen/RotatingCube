#version 430 core

in vec3 fragment_position;
in vec3 fragment_color;
in vec3 fragment_normal;

out vec3 color;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float ambientStrength;

void main(void)
{
	vec3 norm = normalize(fragment_normal);
	vec3 lightDir = normalize(lightPosition - fragment_position);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;


    vec3 ambient = ambientStrength * lightColor;
    vec3 result = (ambient + diffuse) * fragment_color;
    color = result;
	//color = fragment_color;
}