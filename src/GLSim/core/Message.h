#ifndef OGL_MESSAGE_INCLUDED
#define OGL_MESSAGE_INCLUDED

#include "GLSim/core/shadermanager.h"

namespace ogl { class Message; class MessageRender; class MessageUpdatePhysics;  class MessageUpdate; }
class Message
{
public:
	virtual ~Message() { }

	enum MESSAGE_TYPES
	{
		RENDER,
		STEP_PHYSICS,
		UPDATE
	};

	MESSAGE_TYPES getType() const { return m_type; }
protected:
	Message()
		:m_type((MESSAGE_TYPES)-1)
	{ }
	MESSAGE_TYPES m_type;
};

class MessageRender : public Message
{
public:
	MessageRender(float interp, ShaderManager* shaderManager, glm::mat4 VP, bool setMVP)
		: m_interp(interp),
		m_manager(shaderManager),
		m_VP(VP),
		m_setMVP(setMVP)
	{
		m_type = RENDER;
	}
	~MessageRender() { }

	float getInterp() { return m_interp; }
	ShaderManager* getShaderManager() { return m_manager; }
	glm::mat4 getVP() { return m_VP; }
	bool shouldSetMVP() { return m_setMVP; }

private:
	float m_interp;
	ShaderManager* m_manager;
	glm::mat4 m_VP;
	bool m_setMVP;
};

class MessageUpdatePhysics : public Message
{
public:
	MessageUpdatePhysics() 
	{
		m_type = MESSAGE_TYPES::STEP_PHYSICS;
	}
	~MessageUpdatePhysics() { }
};

class MessageUpdate : public Message
{
public:
	MessageUpdate() 
	{ 
		m_type = MESSAGE_TYPES::UPDATE;
	}
	~MessageUpdate() { }
};

#endif