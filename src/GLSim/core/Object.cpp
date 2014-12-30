#include "GLSim/core/Object.h"
#include <type_traits>
#include "GLSim/core/RenderMesh.h"

Object::Object(const std::string& name, const std::string& tag)
	:m_compMap(),
	m_name(name),
	m_tag(tag)
{

}

Object::~Object()
{
	/*for(std::unordered_map<Component::COMPONENT_TYPE, Component*>::iterator i = m_compMap.begin(); i != m_compMap.end(); ++i)
	{
		delete i->second;
	}*/
}

void Object::addComponent(Component* comp)
{
	m_compMap.emplace(comp->getType(), comp);
}
