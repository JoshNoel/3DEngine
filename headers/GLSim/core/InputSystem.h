#ifndef OGL_INPUTSYSTEM_INCLUDED
#define OGL_INPUTSYSTEM_INCLUDED

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLSim/core/window.h"
#include "glm/glm.hpp"

namespace ogl { class InputSystem; }
class InputSystem
{
public:
	static InputSystem& getInstance()
	{
		static InputSystem instance;
		return instance;
	}

	static void update();

	static void setWindow(Window* window);
	static bool getKey(int key);
	static bool getKeyPressed(int key);
	static bool getKeyReleased(int key);

	static bool getMouse(int button);
	static bool getMousePressed(int button);
	static bool getMouseReleased(int button);

	static glm::vec2 getMousePos();
	static glm::vec2 getMouseDelta();
private:
	InputSystem();
	InputSystem(const InputSystem& copy);
	InputSystem& operator=(const InputSystem& copy);

	static Window* m_window;
	static double xpos, ypos;
	static double deltax, deltay;
	static glm::vec2 lastPos;
	static bool firstUpdate;
};


#endif