#ifndef OGL_LIGHT_INCLUDED
#define OGL_LIGHT_INCLUDED

#include "GLSim/core/Component.h"

namespace ogl { class Light; }
class Light : public Component
{
public: 
	enum LIGHT_TYPES
	{
		DIRECTIONAL = 0,
		POINT = 1
	};
	Light(float intensity = 1.0f);
	virtual ~Light();

	void setIntensity(float);
	inline float getIntensity() { return m_intensity; }

	inline void setColor(glm::vec3 v) { m_color = v; }
	inline glm::vec3 getColor() { return m_color; }

	inline void setType(LIGHT_TYPES type) { m_lightType = type; }
	inline LIGHT_TYPES getType() { return m_lightType; }



public:
	float m_intensity;
	glm::vec3 m_color;
	LIGHT_TYPES m_lightType;
	float m_constant;
	float m_linear;
	float m_exp;
};

struct Light_Directional : public Light
{
public:
	Light_Directional(float intensity = 1.0f)
		: Light(intensity)
	{
		m_lightType = DIRECTIONAL;
	}

	~Light_Directional()
	{
	}
};

//Contstant-Linear-Quadratic atten
struct Light_Point : public Light
{
public:
	Light_Point(float intensity = 1.0f)
		: Light(intensity)
	{
		m_lightType = POINT;
		m_constant = 0.0f;
		m_linear = 0.0f;
		m_exp = 1.0f;
	}

	~Light_Point()
	{
	}
	
public:


};

#endif