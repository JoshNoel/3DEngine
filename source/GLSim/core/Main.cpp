#include "GLSim/core/core.h"
#include <thread>


int main(void)
{
	Window window;
	Core core(&window);
	core.run();
	glfwTerminate();
	return 0;
}