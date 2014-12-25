#include "GLSim/core/core.h"
#include <thread>


int main()
{
	Window window;
	Core core(&window);
	core.run();
	glfwTerminate();
	return 0;
}