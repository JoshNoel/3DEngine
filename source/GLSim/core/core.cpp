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
	dirLightTrans1(),
	material(),
	pointLight1(),
	pointLightComp1(),
	pointLightTrans1()
{
	dirLightComp1.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	dirLightTrans1.rotate(glm::vec3(1.0f, 0.0f, 1.0f), 30.0f);
	dirLightComp1.setIntensity(0.8f);
	dirLight1.addComponent(&dirLightComp1);
	dirLight1.addComponent(&dirLightTrans1);
	dirLightComp1.setType(Light::DIRECTIONAL);
	//m_renderSystem.addLight(&dirLight1);

	pointLightComp1.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	pointLightTrans1.translate(glm::vec3(0,2.0,4.0f));
	pointLightComp1.setIntensity(15.0f);
	pointLight1.addComponent(&pointLightComp1);
	pointLight1.addComponent(&pointLightTrans1);
	pointLightComp1.setType(Light::POINT);

	m_renderSystem.addLight(&pointLight1);

	material.setTexIndex(TextureManager::LoadTexture("./res/textures/gradient.png", TEXTURE_2D));
	mesh.unmapped = true;
	floorMesh.unmapped = true;
	m_modelLoader.loadMesh("./res/models/monkey.fbx", &mesh);
	m_modelLoader.loadMesh("./res/models/floor.fbx", &floorMesh);
	mesh.setMaterial(&material);
	floorMesh.setMaterial(&material);
	InputSystem::setWindow(m_window);

	//mesh = std::make_shared<RenderMesh>();
	//mesh.setVertices(data, indices, n);
	transform.translate(glm::vec3(0, 0, 0));
	transform.rotate(glm::vec3(1, 0, 0), -90);
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
	cameraComp.setClearColor(glm::vec3(0,0,.1));
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
	float fpsTime = 0.0f;
	int frameCounter = 0;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
	reverse = false;


	while(!glfwWindowShouldClose(m_window->getWindow())) //&& glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		QueryPerformanceCounter(&endTime);
		deltaTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
		QueryPerformanceCounter(&startTime);
		//convert to microseconds
		deltaTime.QuadPart *= 1000000;
		deltaTime.QuadPart /= frequency.QuadPart;
		accum += double(deltaTime.QuadPart);
		fpsTime += float(deltaTime.QuadPart);
		if (fpsTime >= 1000000.0f)
		{
			fprintf(stdout, "fps: %d\n", int(float(frameCounter) / (fpsTime / 1000000.0f)));
			fpsTime = 0.0f;
			frameCounter = 0;
		}

		while(accum >= PHYSICS_TIMESTEP)
		{
			///physics
			stepPhysics();
			accum -= PHYSICS_TIMESTEP;
		}

		float interp = float(accum / PHYSICS_TIMESTEP);
		m_renderSystem.render(interp, m_window);
		update();		

		frameCounter++;
	}
}


void Core::stepPhysics()
{
	/*if (accumulator >= 2 * 3.14)
		reverse = true;
	if (accumulator <= 0)
		reverse = false;*/
	//steps accumulator once in 5 secs;
	//accumulator += (2.0f*3.1416f / 2.0f)/120;
	//siny = sin(accumulator);
	//cosx = cos(accumulator);

	//fprintf(stdout, "%f\n", siny);

	//pointLightTrans1.translate(glm::vec3((cosx/120)*2, (siny/120)*2, 0.0f));
	InputSystem::update();

	m_physicsSystem.update();
	m_logicSystem.stepPhysics();
}

void Core::update()
{
	glfwPollEvents();
}