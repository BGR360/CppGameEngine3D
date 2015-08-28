#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uvCoord;
layout(location = 2) in vec3 normal;

layout(location = 0) out vec4 outPosition;

void main()
{
	outPosition = vec4(position, 1);
}