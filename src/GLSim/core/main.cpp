#include "GLSim/core/core.h"
#include <thread>


int main()
{
	Window window;
	int width, height;
	glfwGetWindowSize(window.getWindow(), &width, &height);
	Core core(&window, width, height);
	core.run();
	glfwTerminate();
	return 0;
}