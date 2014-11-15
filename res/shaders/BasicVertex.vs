#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 MVP;
uniform mat4 M;

out vec3 worldPos0;
out vec3 normal0;
out vec2 uv0;

void main()
{
	gl_Position = MVP * vec4(pos, 1.0);
	normal0 = normalize(M * vec4(normal, 0)).xyz;
	//normal0 = normal;
	worldPos0 = normalize(M * vec4(pos, 1)).xyz;
	uv0 = uv;
}
