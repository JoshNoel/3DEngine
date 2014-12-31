#version 330 core

layout(location = 3) out vec3 posOut;
layout(location = 1) out vec3 normalOut;
layout(location = 2) out vec3 uvOut;
layout(location = 0) out vec3 diffuseOut;

uniform sampler2D colorSampler;

in vec3 worldPos0;
in vec3 normal0;
in vec2 uv0;

void main()
{
	posOut = worldPos0;
	normalOut = normalize(normal0);
	uvOut = vec3(uv0, 0.0);
	diffuseOut = texture(colorSampler, uv0).xyz;
}