#ifndef OGL_COMPONENT_INCLUDED
#define OGL_COMPONENT_INCLUDED

#include "GLSim/core/Message.h"

namespace ogl { class Component; }
class Component
{
public:
	enum COMPONENT_TYPE
	{
		TRANSFORM = 0,
		RENDER_MESH,
		CAMERA,
		LIGHT
	};

	Component(COMPONENT_TYPE type);
	virtual ~Component();

	COMPONENT_TYPE getType();
	void setType(COMPONENT_TYPE type) { m_type = type; }
	virtual void receiveMessage(Message&);

protected:
	COMPONENT_TYPE m_type;
};

#endif