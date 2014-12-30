#ifndef OGL_RENDERSYSTEM_INCLUDED
#define OGL_RENDERSYSTEM_INCLUDED

#include "GLSim/core/System.h"
#include "GL/glew.h"
#include "GLSim/core/shadermanager.h"
#include "GLSim/core/window.h"
#include "GLSim/core/Object.h"
#include "GLSim/core/Light.h"

namespace ogl { class RenderSystem; }
class RenderSystem : public System
{
public:
	RenderSystem(bool deferred = false);
	~RenderSystem();

	void render(float interp, Window* window);
	void setCamera(Object*);
	bool addLight(Object*);

	void setDeferred(bool v);
	bool isDeferred();

private:
	ShaderManager m_shaderManager;
	Object* p_camera;

	bool m_deferred;

	std::vector<Object*> m_dirLightList;
	std::vector<Object*> m_pointLightList;

};

#endif