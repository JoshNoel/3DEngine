#ifndef OGL_LIGHT_INCLUDED
#define OGL_LIGHT_INCLUDED

#include "GLSim/core/Component.h"

namespace ogl { class Light; }
class Light : public Component
{
public: 
	enum LIGHT_TYPES
	{
		DIRECTIONAL
	};
	Light(float intensity = 1.0f);
	virtual ~Light();

	void setIntensity(float);
	inline float getIntensity() { return m_intensity; }

	inline void setColor(glm::vec3 v) { m_color = v; }
	inline glm::vec3 getColor() { return m_color; }

	inline LIGHT_TYPES getLightType() { return m_lightType; }

protected:
	float m_intensity;
	glm::vec3 m_color;
	LIGHT_TYPES m_lightType;
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

#endif