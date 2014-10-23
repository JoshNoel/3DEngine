#ifndef OGL_LOGIC_INCLUDED
#define OGL_LOGIC_INCLUDED

#include "GLSim/core/Object.h"

namespace ogl { class Logic; }
class Logic
{
public:
	Logic(std::vector<Component::COMPONENT_TYPE> requiredComponents, const std::string& name = "");
	virtual ~Logic();

	void setObjectList(std::vector<Object*>*);
	bool setParent(Object* obj);
	inline Object* getParent() { return m_parent; }

	virtual void receiveMessage(Message&);

	inline std::string& getName() { return m_name; }
protected:
	std::vector<Object*>* m_objectList;
	Object* m_parent;
	std::string m_name;
	std::vector<Component::COMPONENT_TYPE> m_requiredComponents;
};

#endif