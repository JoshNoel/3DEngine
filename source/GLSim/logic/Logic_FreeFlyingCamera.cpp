#include "GLSim/logic/Logic_FreeFlyingCamera.h"
#include "GLSim/core/InputSystem.h"

Logic_FreeFlyingCamera::Logic_FreeFlyingCamera()
	: Logic(std::vector<Component::COMPONENT_TYPE>(Component::COMPONENT_TYPE::TRANSFORM), "FreeFlyingCamera")
{

}

Logic_FreeFlyingCamera::~Logic_FreeFlyingCamera()
{
	
}

void Logic_FreeFlyingCamera::update()
{
	if(InputSystem::getInstance().getKey(GLFW_KEY_W))
	{
		m_parent->getComponent<Transform>()->translate(glm::vec3(0, 0, -m_moveSpeed));
	}
	if(InputSystem::getInstance().getKey(GLFW_KEY_A))
	{
		m_parent->getComponent<Transform>()->translate(glm::vec3(-m_moveSpeed, 0, 0));
	}
	if(InputSystem::getInstance().getKey(GLFW_KEY_S))
	{
		m_parent->getComponent<Transform>()->translate(glm::vec3(0, 0, m_moveSpeed));
	}
	if(InputSystem::getInstance().getKey(GLFW_KEY_D))
	{
		m_parent->getComponent<Transform>()->translate(glm::vec3(m_moveSpeed, 0, 0));
	}
	if(InputSystem::getInstance().getMouseDelta().x != 0)
	{
		//todo: Epsilon comparison
		//todo: Local rotation
		m_parent->getComponent<Transform>()->rotate(glm::vec3(0, 1, 0), InputSystem::getInstance().getMouseDelta().x * m_mouseSens);
	}
	if(InputSystem::getInstance().getMouseDelta().y != 0)
	{
		//todo: Epsilon comparison
		//todo: Local rotation
		/*m_parent->getComponent<Transform>()->rotate(glm::cross(m_parent->getComponent<Transform>()->getUp(), m_parent->getComponent<Transform>()->getForward()),
			InputSystem::getInstance().getMouseDelta().y * m_mouseSens);*/
		m_parent->getComponent<Transform>()->rotate(glm::vec3(1,0,0), InputSystem::getInstance().getMouseDelta().y * m_mouseSens);
	}
}

void Logic_FreeFlyingCamera::receiveMessage(Message& m)
{
	switch(m.getType())
	{
	case Message::RENDER:
	{
		
	}
		break;
	case Message::STEP_PHYSICS:
		update();
		break;
	}
}

