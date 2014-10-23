#include "GLSim/core/window.h"
#include <stdio.h>
#include <stdlib.h>


static void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window()
{
	/* Initialize the library */
	if(!glfwInit())
		fprintf(stdout, "error initializing glfw");


	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifndef NDEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(800, 600, "3D Sim", NULL, NULL);//960 540
	if(!m_window)
	{
		glfwTerminate();
		fprintf(stdout, "error creating a window\n");
	}

	glfwSetWindowSizeCallback(m_window, resizeCallback);


	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);

	GLenum err = glewInit();
	glewExperimental = GL_TRUE;
	if(GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}


Window::~Window()
{
	glfwDestroyWindow(m_window);
}



GLFWwindow* Window::getWindow()
{
	return m_window;
}
