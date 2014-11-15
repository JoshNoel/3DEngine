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
	floorTransform(),
	floorMesh(),
	floor(),
	m_renderSystem(),
	m_logicSystem(),
	m_physicsSystem(),
	logicCamera(),
	m_modelLoader(),
	m_textureManager(),
	dirLight1(),
	dirLightComp1(),
	dirLightTrans1()
{
	dirLightComp1.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	dirLightTrans1.rotate(glm::vec3(1.0f, 0.0f, 0.5f), 15.0f);
	dirLightComp1.setIntensity(0.5f);
	dirLight1.addComponent(&dirLightComp1);
	dirLight1.addComponent(&dirLightTrans1);
	m_renderSystem.addLight(&dirLight1);

	m_modelLoader.loadMesh("C:/Projects/3DSim/res/models/sphere.fbx", &mesh);
	m_modelLoader.loadMesh("C:/Projects/3DSim/res/models/floor.fbx", &floorMesh);
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
	//mesh.setVertices(data, indices, n);
	transform.translate(glm::vec3(0, 0, 0));
	cube.addComponent(&transform);
	cube.addComponent(&mesh);

	floorTransform.translate(glm::vec3(0.0f, -2.0f, 0.0f));
	floorTransform.scale(glm::vec3(5.0f, 5.0f, 5.0f));
	floor.addComponent(&floorTransform);
	floor.addComponent(&floorMesh);

	cameraTransform.setCameraMode(true);
	cameraTransform.translate(glm::vec3(0, 0, 6));
	cameraComp.setAmbientColor(glm::vec3(1.0f, 1.0f, 1.0f));
	cameraComp.setAmbientIntensity(0.1f);
	camera.addComponent(&cameraComp);
	camera.addComponent(&cameraTransform);

	m_logicSystem.addListener(&logicCamera, &camera);
	m_renderSystem.setCamera(&camera);
	m_renderSystem.addListener(&transform);
	m_renderSystem.addListener(&mesh);
	m_renderSystem.addListener(&floorTransform);
	m_renderSystem.addListener(&floorMesh);
	m_physicsSystem.addListener(&transform);
	m_physicsSystem.addListener(&cameraTransform);
	m_physicsSystem.addListener(&floorTransform);
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