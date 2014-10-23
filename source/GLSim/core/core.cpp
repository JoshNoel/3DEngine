#include "GLSim/core/core.h"
#include <Windows.h>
#include "GLSim/core/RenderMesh.h"

Core::Core(Window* window)
	:m_window(window),
	cube("Cube"),
	camera("Camera", ogl::tags.at((int)ogl::DEFAULT_TAGS::TAG_CAMERA)),
	cameraComp(),
	cameraTransform(),
	transform(),
	mesh(),
	m_renderSystem(),
	m_logicSystem(),
	m_physicsSystem(),
	logicCamera(),
	m_modelLoader(),
	dirLight1(),
	dirLightComp1(),
	dirLightTrans1()
{
	dirLightComp1.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	dirLight1.addComponent(&dirLightComp1);
	dirLight1.addComponent(&dirLightTrans1);
	m_renderSystem.addLight(&dirLight1);

	m_modelLoader.loadMesh("C:/Projects/3DSim/res/models/cube.obj", &mesh);
	InputSystem::setWindow(m_window);
	/*static std::vector<GLfloat> data = {
		-1.0f, -1.0f, -1.0f, // triangle 1 : begin
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f, -1.0f, // triangle 2 : begin
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f, // triangle 2 : end
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};*/
	//mesh = std::make_shared<RenderMesh>();
	static std::vector<GLfloat> data = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	std::vector<GLushort> indices = { 
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2 };
	std::vector<float> n;
	//mesh.setVertices(data, indices, n);
	transform.setPosition(glm::vec3(0, 0, 0));
	cube.addComponent(&transform);
	cube.addComponent(&mesh);
	cameraTransform.setCameraMode(true);
	cameraTransform.setPosition(glm::vec3(0, 0, 6));
	cameraComp.setAmbientColor(glm::vec3(1.0f, 1.0f, 1.0f));
	cameraComp.setAmbientIntensity(0.2f);
	camera.addComponent(&cameraComp);
	camera.addComponent(&cameraTransform);
	m_logicSystem.addListener(&logicCamera, &camera);
	m_renderSystem.setCamera(&camera);
	m_renderSystem.addListener(&transform);
	m_renderSystem.addListener(&mesh);
	m_physicsSystem.addListener(&transform);
	m_physicsSystem.addListener(&cameraTransform);
}

Core::~Core()
{

}

void Core::run()
{
	LARGE_INTEGER startTime, endTime, frequency;
	LARGE_INTEGER deltaTime;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);

	while(!glfwWindowShouldClose(m_window->getWindow())) //&& glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		QueryPerformanceCounter(&endTime);
		deltaTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
		//convert to microseconds
		deltaTime.QuadPart *= 1000000;
		deltaTime.QuadPart /= frequency.QuadPart;
		accum += double(deltaTime.QuadPart);
		while(accum >= PHYSICS_TIMESTEP)
		{
			///physics
			stepPhysics();
			accum -= PHYSICS_TIMESTEP;
		}

		float interp = float(accum / PHYSICS_TIMESTEP);
		m_renderSystem.render(interp, m_window);
		update();
	}
}


void Core::stepPhysics()
{
	m_physicsSystem.update();
	m_logicSystem.stepPhysics();
	InputSystem::update();
}

void Core::update()
{
	glfwPollEvents();
}