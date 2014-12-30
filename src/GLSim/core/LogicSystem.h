#ifndef OGL_LOGICSYSTEM_INCLUDED
#define OGL_LOGICSYSTEM_INCLUDED

#include "GLSim/core/System.h"
#include "GLSim/core/Logic.h"

namespace ogl { class LogicSystem; }
class LogicSystem : public System
{
public:
	LogicSystem();
	~LogicSystem();

	void stepPhysics();
	void addListener(Logic*, Object*);
	void sendMessage(Message&);

private:
	std::vector<Logic*> m_logicList;
};

#endif