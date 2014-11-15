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

namespace ogl { class Core; }
class Core
{
public:
	Core(Window*);
	~Core();

	void run();
	void update();
	void stepPhysics();

private:
	Window* m_window;
	RenderSystem m_renderSystem;
	LogicSystem m_logicSystem;
	PhysicsSystem m_physicsSystem;

	ModelLoader m_modelLoader;
	TextureManager m_textureManager;


	Object cube;
	Object camera;
	Camera cameraComp;
	Transform cameraTransform;

	Logic_FreeFlyingCamera logicCamera;

	RenderMesh mesh;
	Transform transform;

	Object floor;
	RenderMesh floorMesh;
	Transform floorTransform;

	Object dirLight1;
	Light_Directional dirLightComp1;
	Transform dirLightTrans1;

	const double PHYSICS_TIMESTEP = 1000000.0 / 120.0;
	double accum = 0.0;
};

#endif
