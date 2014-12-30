#include "GLSim/core/Light.h"

Light::Light(float intensity)
	: Component(Component::COMPONENT_TYPE::LIGHT),
	m_intensity(intensity),
	m_lightType(DIRECTIONAL)
{
}

Light::~Light()
{
}

void Light::setIntensity(float i)
{
	m_intensity = i;
}