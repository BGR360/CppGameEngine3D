#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uvCoord;
layout(location = 2) in vec3 normal;

uniform vec3 color;
uniform sampler2D tex;

out vec4 outColor;

vec4 makeNegative(vec4 color)
{
	return vec4(1 - color.x, 1 - color.y, 1 - color.z, 1);
}

void main()
{
	outColor = texture2D(tex, uvCoord);
}