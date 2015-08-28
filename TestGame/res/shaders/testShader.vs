#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uvCoord;
layout(location = 2) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) out vec4 outPosition;
layout(location = 1) out vec2 outUvCoord;
layout(location = 2) out vec3 outNormal;

void main()
{
	vec4 transformedPosition;
	transformedPosition = vec4(position, 1);
	transformedPosition = projectionMatrix * viewMatrix * modelMatrix * transformedPosition;
	outPosition = transformedPosition;
	
	outUvCoord = uvCoord;
	outNormal = normal;
}