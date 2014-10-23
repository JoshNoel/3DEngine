#include "GLSim/core/Component.h"

Component::Component(COMPONENT_TYPE type)
	:m_type(type)
{
	
}

Component::~Component()
{

}

Component::COMPONENT_TYPE Component::getType()
{
	return m_type;
}

void Component::receiveMessage(Message& message)
{

}