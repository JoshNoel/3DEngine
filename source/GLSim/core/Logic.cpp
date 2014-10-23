#include "GLSim/core/Logic.h"

Logic::Logic(std::vector<Component::COMPONENT_TYPE> requiredComponents, const std::string& name)
	:m_requiredComponents(requiredComponents),
	m_name(name)
{

}

Logic::~Logic()
{

}

void Logic::setObjectList(std::vector<Object*>* vector)
{
	m_objectList = vector;
}

bool Logic::setParent(Object* parent)
{
	for(Component::COMPONENT_TYPE comp : m_requiredComponents)
	{
		switch(comp)
		{
		case Component::TRANSFORM:
		{
			if(parent->getComponent<Transform>() == nullptr)
			{
				//TODO: Message Boxes
				fprintf(stdout, "Parent object, %s, does not have required TRANSFORM component, for logic, %s", parent->getName(), m_name);
				return false;
			}
		}
			break;
		case Component::RENDER_MESH:
		{
			if(parent->getComponent<RenderMesh>() == nullptr)
			{
				//TODO: Message Boxes
				fprintf(stdout, "Parent object, %s, does not have required RENDER MESH component, for logic, %s", parent->getName(), m_name);
				return false;
			}
		}
			break;
		case Component::CAMERA:
		{
			if(parent->getComponent<Camera>() == nullptr)
			{
				//TODO: Message Boxes
				fprintf(stdout, "Parent object, %s, does not have required CAMERA component, for logic, %s", parent->getName(), m_name);
				return false;
			}
		}
			break;
		default:
			break;
		}
	}
	m_parent = parent;
	return true;
}

void Logic::receiveMessage(Message& message)
{

}