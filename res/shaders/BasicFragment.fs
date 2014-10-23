#version 330 core

in vec3 normal0;
out vec4 FragColor;

struct Camera
{
	float ambientIntensity;
	vec3 ambientColor;
};

struct Light
{
	float intensity;
	vec3 color;
};

struct DirLight
{
	Light light;
	vec3 direction;
};

uniform Camera camera;

const int maxDirLights = 6;

uniform DirLight dirLights[maxDirLights];
uniform int numDirLights;

void main()
{
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	vec4 baseColor = vec4(0.33, 0.55, 0.99, 1.0);
	vec4 ambientColor = vec4(camera.ambientColor, 1.0) *camera.ambientIntensity;
	vec4 dirLightsColor = vec4(0,0,0,0);
	float diffuseF;
	
	for(int i = 0; i < numDirLights; ++i)
	{
		diffuseF = dot(normalize(normal0), -dirLights[i].direction);
		if(diffuseF > 0)
		{
			dirLightsColor += vec4(dirLights[i].light.color, 1.0) * dirLights[i].light.intensity * diffuseF;
		}
	}
	
	FragColor = vec4(normal0, 1.0);//baseColor * (ambientColor + dirLightsColor);
}