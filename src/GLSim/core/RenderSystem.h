#ifndef OGL_RENDERSYSTEM_INCLUDED
#define OGL_RENDERSYSTEM_INCLUDED

#include "GLSim/core/System.h"
#include "GL/glew.h"
#include "GLSim/core/shadermanager.h"
#include "GLSim/core/window.h"
#include "GLSim/core/Object.h"
#include "GLSim/core/Light.h"
#include "GLSim\core\GBuffer.h"

namespace ogl { class RenderSystem; }
class RenderSystem : public System
{
public:
	RenderSystem(int width, int height, bool deferred = true);
	~RenderSystem();

	void render(float interp, Window* window);
	void setCamera(Object*);
	bool addLight(Object*);

	void setDeferred(bool v);
	bool isDeferred();

	void setCheckGBuffer(bool v) { m_checkGBuffer = v; }

private:
	ShaderManager m_shaderManager;
	Object* p_camera;

	bool m_deferred;
	bool m_checkGBuffer;

	std::vector<Object*> m_dirLightList;
	std::vector<Object*> m_pointLightList;

	GBuffer m_gbuffer;
};

#endif