#ifndef OGL_SYSTEM_INCLUDED
#define OGL_SYSTEM_INCLUDED
#include "GLSim/core/Message.h"
#include <vector>
#include "GLSim/core/Component.h"
#include "GLSim/core/Object.h"
#include <memory>

namespace ogl { class System; }
class System
{
public:
	System();
	virtual ~System();

	virtual void addListener(Component* comp);
	void addObject(Object* obj);

protected:
	void sendMessage(Message&);
	std::vector<Component*> m_eventListeners;
	std::vector<Object*> m_objects;
};
#endif