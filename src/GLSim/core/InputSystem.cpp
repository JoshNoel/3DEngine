#include "GLSim/core/InputSystem.h"

InputSystem::InputSystem()
{

}

void InputSystem::setWindow(Window* window)
{
	m_window = window;
}
bool InputSystem::getKeyPressed(int key)
{
	switch(glfwGetKey(m_window->getWindow(), key))
	{
	case GLFW_PRESS:
		return true;
	case GLFW_RELEASE:
		return false;
	case GLFW_REPEAT:
		return false;
	}
}

bool InputSystem::getKeyReleased(int key)
{
	switch(glfwGetKey(m_window->getWindow(), key))
	{
	case GLFW_PRESS:
		return false;
	case GLFW_RELEASE:
		return true;
	case GLFW_REPEAT:
		return false;
	}
}

bool InputSystem::getKey(int key)
{
	switch(glfwGetKey(m_window->getWindow(), key))
	{
	case GLFW_PRESS:
		return true;
	case GLFW_RELEASE:
		return false;
	case GLFW_REPEAT:
		return true;
	}
}

bool InputSystem::getMousePressed(int button)
{
	switch(glfwGetMouseButton(m_window->getWindow(), button))
	{
	case GLFW_PRESS:
		return true;
	case GLFW_RELEASE:
		return false;
	case GLFW_REPEAT:
		return false;
	}
}

bool InputSystem::getMouseReleased(int button)
{
	switch(glfwGetMouseButton(m_window->getWindow(), button))
	{
	case GLFW_PRESS:
		return false;
	case GLFW_RELEASE:
		return true;
	case GLFW_REPEAT:
		return false;
	}
}

bool InputSystem::getMouse(int button)
{
	switch(glfwGetMouseButton(m_window->getWindow(), button))
	{
	case GLFW_PRESS:
		return true;
	case GLFW_RELEASE:
		return false;
	case GLFW_REPEAT:
		return true;
	}
}

glm::vec2 InputSystem::getMousePos()
{
	return glm::vec2(xpos, ypos);
}

void InputSystem::update()
{
	if(firstUpdate)
	{
		glfwSetInputMode(m_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(m_window->getWindow(), &xpos, &ypos);
		firstUpdate = false;
	}
	if(glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE))
	{
		glfwSetInputMode(m_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	lastPos = glm::vec2(xpos, ypos);
	glfwGetCursorPos(m_window->getWindow(), &xpos, &ypos);

	deltax = lastPos.x - xpos;
	deltay = lastPos.y - ypos;
}

glm::vec2 InputSystem::getMouseDelta()
{
	return glm::vec2(deltax, deltay);
}



Window* InputSystem::m_window = nullptr;
double InputSystem::xpos;
double InputSystem::ypos;
double InputSystem::deltax;
double InputSystem::deltay;
glm::vec2 InputSystem::lastPos;
bool InputSystem::firstUpdate = true;
