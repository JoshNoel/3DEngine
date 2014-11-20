#include "GLSim/core/window.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "CEGUI\RendererModules\OpenGL\GL3Renderer.h"
#include "CEGUI\CEGUI.h"



static void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(width, height));
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

	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if(GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));


	CEGUI::OpenGL3Renderer& renderer = CEGUI::OpenGL3Renderer::bootstrapSystem();
	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
	rp->setResourceGroupDirectory("imagesets", "C:/Projects/3DSim/res/cegui/imagesets/");
	rp->setResourceGroupDirectory("fonts", "C:/Projects/3DSim/res/cegui/fonts/");
	rp->setResourceGroupDirectory("animations", "C:/Projects/3DSim/res/cegui/animations/");
	rp->setResourceGroupDirectory("layouts", "C:/Projects/3DSim/res/cegui/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "C:/Projects/3DSim/res/cegui/looknfeel/");
	rp->setResourceGroupDirectory("luaScripts", "C:/Projects/3DSim/res/cegui/lua_scripts/");
	rp->setResourceGroupDirectory("xmlSchemas", "C:/Projects/3DSim/res/cegui/xml_schemas/");
	rp->setResourceGroupDirectory("schemes", "C:/Projects/3DSim/res/cegui/schemes/");





	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-12");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	//CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "_MasterRoot");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("TextDemo.layout");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);
	CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(800, 600));
}


Window::~Window()
{
	glfwDestroyWindow(m_window);
}



GLFWwindow* Window::getWindow()
{
	return m_window;
}
