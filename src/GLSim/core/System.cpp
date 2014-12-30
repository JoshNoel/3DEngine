#include "GLSim/core/System.h"
System::System()
{

}

System::~System()
{
}

void System::addListener(Component* comp)
{
	m_eventListeners.push_back(comp);
}

void System::addObject(Object* obj)
{
	m_objects.push_back(obj);
}

void System::sendMessage(Message& message)
{
	for(unsigned int i = 0; i < m_eventListeners.size(); ++i)
	{
		if(m_eventListeners[i] != nullptr)
			m_eventListeners.at(i)->receiveMessage(message);
		else
		{
			m_eventListeners.erase(m_eventListeners.begin() + i);
			m_eventListeners.shrink_to_fit();
		}
	}
}