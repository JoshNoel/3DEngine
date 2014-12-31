#ifndef OGL_CORE_INCLUDED
#define OGL_CORE_INCLUDED

#include "GLSim/core/window.h"
#include "GLSim/core/Object.h"
#include "GLSim/core/RenderMesh.h"
#include "GLSim/core/RenderSystem.h"
#include "GLSim/core/InputSystem.h"
#include "GLSim/core/LogicSystem.h"
#include "GLSim/core/PhysicsSystem.h"
#include "GLSim/core/Transform.h"
#include "GLSim/core/Camera.h"
#include "GLSim/logic/Logic_FreeFlyingCamera.h"
#include "GLSim/core/ModelLoader.h"
#include "GLSim/core/Light.h"
#include "GLSim/core/TextureManager.h"
#include <climits>

namespace ogl { class Core; }
class Core
{
public:
	Core(Window*, int, int);
	~Core();

	void run();
	void update();
	void stepPhysics();

private:
	Window* m_window;

	//Systems
	RenderSystem m_renderSystem;
	LogicSystem m_logicSystem;
	PhysicsSystem m_physicsSystem;

	ModelLoader m_modelLoader;
	TextureManager m_textureManager;

	
	//Objects
	Object camera;
	Camera cameraComp;
	Transform cameraTransform;

	Object scene;
	Transform transform;
	RenderMesh mesh;

	//Camera
	Logic_FreeFlyingCamera logicCamera;


	//Lights
	Object dirLight1;
	Light_Directional dirLightComp1;
	Transform dirLightTrans1;

	Object pointLight1;
	Light_Point pointLightComp1;
	Transform pointLightTrans1;

	const double PHYSICS_TIMESTEP = 1000000.0 / 120.0;
	double accum = 0.0;


	///////////////TEST//////////////////
	float siny;
	float cosx;
	float accumulator;
	float theta;
	bool reverse;
};

#endif
