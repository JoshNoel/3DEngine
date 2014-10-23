#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

uniform mat4 MVP;
uniform mat4 M;

out vec3 normal0;

void main()
{
	gl_Position = MVP * vec4(pos, 1.0);
	normal0 = normal;//normalize(M * vec4(normal, 0)).xyz;
}
