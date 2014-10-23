#include "GLSim/core/LogicSystem.h"

LogicSystem::LogicSystem()
{

}

LogicSystem::~LogicSystem()
{

}

void LogicSystem::stepPhysics()
{
	sendMessage(MessageUpdatePhysics());
}

void LogicSystem::sendMessage(Message& m)
{
	for(unsigned int i = 0; i < m_logicList.size(); ++i)
	{
		if(m_logicList[i] != nullptr)
			m_logicList.at(i)->receiveMessage(m);
		else
		{
			m_logicList.erase(m_logicList.begin() + i);
			m_logicList.shrink_to_fit();
		}
	}
}

void LogicSystem::addListener(Logic* logic, Object* objLink)
{
	logic->setParent(objLink);
	logic->setObjectList(&m_objects);
	m_logicList.push_back(logic);
}