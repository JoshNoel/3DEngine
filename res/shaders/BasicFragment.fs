#version 330 core

smooth in vec3 normal0;
in vec2 uv0;
in vec3 worldPos0;
//in mat4 M;
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

struct PointLight
{
	Light light;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

uniform Camera camera;

const int maxDirLights = 6;
const int maxPointLights = 6;


uniform DirLight dirLights[maxDirLights];
uniform int numDirLights;

uniform PointLight pointLights[maxPointLights];
uniform int numPointLights;

uniform sampler2D tex;

vec4 calcBaseLight(Light light, vec3 direction, vec3 normal);
vec4 calcDirLight(DirLight dirLight, vec3 normal);
vec4 calcPointLight(PointLight pLight, vec3 normal);

void main()
{
	//normal0 = normalize(transpose(inverse(M)) * vec4(normal0, 0)).xyz;
	//pos0 = normalize(M * vec4(pos0, 1)).xyz;
	//FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	vec4 baseColor = texture(tex, uv0); //vec4(0.33, 0.55, 0.99, 1.0);// texture(tex, uv0);// + vec4(0.33, 0.55, 0.99, 1.0);//vec4(0,uv0.x, uv0.y,0);////
	vec4 lightTotal = vec4(camera.ambientColor, 1.0) *camera.ambientIntensity;
	
	for(int i = 0; i < numDirLights; ++i)
	{
		lightTotal += calcDirLight(dirLights[i], normal0);
	}
	
	for(int i = 0; i < numPointLights; ++i)
	{
		lightTotal += calcPointLight(pointLights[i], normal0);
	}
	
	lightTotal = clamp(lightTotal,0,1);

	FragColor = baseColor * lightTotal;
}

vec4 calcBaseLight(Light light, vec3 direction, vec3 normal)
{
	vec4 diffuseColor = vec4(0,0,0,0);
	float diffuseF = dot(normal, -direction);
	
	if(diffuseF > 0)
	{
		diffuseColor = vec4(light.color, 1.0) * light.intensity * diffuseF;
	}
	
	return diffuseColor;
}

vec4 calcDirLight(DirLight dirLight, vec3 normal)
{
	return calcBaseLight(dirLight.light, dirLight.direction, normal);
}

vec4 calcPointLight(PointLight pLight, vec3 normal)
{
	vec3 lightToSurface = worldPos0 - pLight.position;
	float dist = length(lightToSurface);
	lightToSurface = normalize(lightToSurface);
	
	vec4 color = calcBaseLight(pLight.light, lightToSurface, normal);
	

	//attemuation is 1/(const + linear*d + exp*d*d)
	return color/(pLight.constant + pLight.linear*dist + pLight.exponent*dist*dist +.0001);
}









