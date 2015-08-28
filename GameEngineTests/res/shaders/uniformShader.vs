#version 130 core

uniform vec3 position;
uniform vec3 translation;
uniform vec2 xyScale;

void main()
{
	vec3 newPosition = vec3(position.x * xyScale.x, position.y * xyScale.y, position.z);
	newPosition += translation;
	
	gl_Position = vec4(newPosition, 1);
}