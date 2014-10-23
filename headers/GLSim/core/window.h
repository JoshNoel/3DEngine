#ifndef OGL_WINDOW_INCLUDED
#define OGL_WINDOW_INCLUDED

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <stdio.h>

namespace ogs {class Window;}
class Window
{
public:
	Window();
	~Window();

	GLFWwindow* getWindow();

private:
	GLFWwindow* m_window;
};
#endif
