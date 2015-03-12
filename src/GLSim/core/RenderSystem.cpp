#include "GLSim/core/RenderSystem.h"
#include "GLSim/core/Transform.h"
#include <Windows.h>
#include "GLFW\glfw3.h"
#ifdef _WIN64
#define CPSTR LPCWSTR
#else
#define CPSTR LPCSTR
#endif

//TODO resize gbuffer dynamically with window
RenderSystem::RenderSystem(int width, int height, bool shouldDefer)
	:m_shaderManager(),
	m_deferred(shouldDefer),
	m_gbuffer(width, height),
	m_checkGBuffer(true)
{
	if(!m_deferred)
	{
		if(!m_shaderManager.addShader(ShaderManager::SHADER_TYPE::VERTEX, "C:/Projects/3DSim/res/shaders/BasicVertex.vs", 0))
			fprintf(stdout, "Error adding Vertex Shader\n");
		if(!m_shaderManager.addShader(ShaderManager::SHADER_TYPE::FRAGMENT, "C:/Projects/3DSim/res/shaders/BasicFragment.fs", 0))
			fprintf(stdout, "Error adding Fragment Shader\n");
	}
	else
	{

		////loc 0: Position
		////loc 1: Normal
		////loc 2: UV
		////loc 3: Diffuse
		if(!m_shaderManager.addShader(ShaderManager::SHADER_TYPE::VERTEX, "C:/Projects/3DSim/res/shaders/d_mesh.vs", 0))
			fprintf(stdout, "Error adding Vertex Shader\n");
		if(!m_shaderManager.addShader(ShaderManager::SHADER_TYPE::FRAGMENT, "C:/Projects/3DSim/res/shaders/d_mesh.fs", 0))
			fprintf(stdout, "Error adding Fragment Shader\n");
		if(!m_shaderManager.addShader(ShaderManager::SHADER_TYPE::VERTEX, "C:/Projects/3DSim/res/shaders/d_light.vs", 1))
			fprintf(stdout, "Error adding Vertex Shader\n");
		if(!m_shaderManager.addShader(ShaderManager::SHADER_TYPE::FRAGMENT, "C:/Projects/3DSim/res/shaders/d_pointlight.fs", 1))
			fprintf(stdout, "Error adding Fragment Shader\n");
		if(!m_shaderManager.addShader(ShaderManager::SHADER_TYPE::VERTEX, "C:/Projects/3DSim/res/shaders/d_light.vs", 2))
			fprintf(stdout, "Error adding Vertex Shader\n");
		if(!m_shaderManager.addShader(ShaderManager::SHADER_TYPE::FRAGMENT, "C:/Projects/3DSim/res/shaders/d_dirlight.fs", 2))
			fprintf(stdout, "Error adding Fragment Shader\n");
	}
	/*
	/2D texture for each attribute + depth
	/Create Framebuffer textures from 2d textures (glFramebufferTexture2D)
	/attach textures to FBO using drawbuffers + color attachments
	/
	/
	*/

	m_shaderManager.linkProgram(0);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

RenderSystem::~RenderSystem()
{
	
}

void RenderSystem::setCamera(Object* camera)
{
	p_camera = camera;
	glm::vec3 color = p_camera->getComponent<Camera>()->getClearColor();
	glClearColor(color.x, color.y, color.z, 1.0);
}

bool RenderSystem::isDeferred()
{ 
	return m_deferred;
}

void RenderSystem::setDeferred(bool v)
{
	m_deferred = v;
}

bool RenderSystem::addLight(Object* l)
{
	if(l->getComponent<Light>() != nullptr)
	{
		//int i = l->getComponent<Light>()->getType();
		switch(l->getComponent<Light>()->getType())
		{
		case Light::LIGHT_TYPES::DIRECTIONAL:
			m_dirLightList.push_back(l);
			break;
		case Light::LIGHT_TYPES::POINT:
			m_pointLightList.push_back(l);
			break;
		default:
			break;
		}
		return true;
	}
	return false;

}

void RenderSystem::render(float interp, Window* window)
{
	//////FORWARD/////
	if(p_camera && !m_deferred)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_shaderManager.useProgram(0);

		p_camera->getComponent<Transform>()->receiveMessage(MessageRender(interp, &m_shaderManager, glm::mat4(1.0), false));
		p_camera->getComponent<Camera>()->receiveMessage(MessageRender(interp, &m_shaderManager, glm::mat4(1.0), false));

		Transform* cam = p_camera->getComponent<Transform>();
		glm::mat4 view = glm::inverse(cam->getTranslationMat() * cam->getRotationMat());
		
		///////////////Directional Lights//////////////////////////
		for(unsigned int i = 0; i < m_dirLightList.size(); ++i)
		{
			m_shaderManager.setUniform("dirLights[" + std::to_string(i) + "].light.color", m_dirLightList[i]->getComponent<Light>()->getColor());//m_dirLightList[i]->getComponent<Light>()->getColor());
			m_shaderManager.setUniform("dirLights[" + std::to_string(i) + "].light.intensity", m_dirLightList[i]->getComponent<Light>()->getIntensity());
			m_shaderManager.setUniform("dirLights[" + std::to_string(i) + "].direction", m_dirLightList[i]->getComponent<Transform>()->getOrientation() * glm::vec3(0, -1, 0));
		}
		m_shaderManager.setUniform("numDirLights", int(m_dirLightList.size()));

		///////////////Point Lights//////////////////////////
		for (unsigned int i = 0; i < m_pointLightList.size(); ++i)
		{
			m_shaderManager.setUniform("pointLights[" + std::to_string(i) + "].light.color", m_pointLightList[i]->getComponent<Light>()->getColor());
			m_shaderManager.setUniform("pointLights[" + std::to_string(i) + "].light.intensity", m_pointLightList[i]->getComponent<Light>()->getIntensity());
			m_shaderManager.setUniform("pointLights[" + std::to_string(i) + "].linear", m_pointLightList[i]->getComponent<Light>()->m_linear);
			m_shaderManager.setUniform("pointLights[" + std::to_string(i) + "].constant", m_pointLightList[i]->getComponent<Light>()->m_constant);
			m_shaderManager.setUniform("pointLights[" + std::to_string(i) + "].position", m_pointLightList[i]->getComponent<Transform>()->getPosition());
			m_shaderManager.setUniform("pointLights[" + std::to_string(i) + "].exponent", m_pointLightList[i]->getComponent<Light>()->m_exp);
		}
		m_shaderManager.setUniform("numPointLights", int(m_pointLightList.size()));

		sendMessage(MessageRender(interp, &m_shaderManager, p_camera->getComponent<Camera>()->getPerspective() * view, true));
	}

	//////DEFERRED/////
	else if(p_camera && m_deferred)
	{
		/////GEOMETRY PASS////////
		m_gbuffer.bindDraw();

		glDisable(GL_BLEND);
		glDepthMask(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_shaderManager.useProgram(0);

		p_camera->getComponent<Transform>()->receiveMessage(MessageRender(interp, &m_shaderManager, glm::mat4(1.0), false));
		p_camera->getComponent<Camera>()->receiveMessage(MessageRender(interp, &m_shaderManager, glm::mat4(1.0), false));
		Transform* cam = p_camera->getComponent<Transform>();
		glm::mat4 view = glm::inverse(cam->getTranslationMat() * cam->getRotationMat());

		sendMessage(MessageRender(interp, &m_shaderManager, p_camera->getComponent<Camera>()->getPerspective() * view, true));
		
		/////LIGHTING PASS///////
		

		if(!m_checkGBuffer)
		{
			glDepthMask(false);
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendEquation(GL_FUNC_ADD);
			glBlendFunc(GL_ONE, GL_ONE);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			m_gbuffer.bindRead();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_shaderManager.useProgram(1);
			sendMessage(MessageRender(interp, &m_shaderManager, p_camera->getComponent<Camera>()->getPerspective() * view, true));
		}
		else
		{
			int width, height;
			glfwGetWindowSize(window->getWindow(), &width, &height);

			int HalfWidth = (width / 2.0f);
			int HalfHeight = (height / 2.0f);
			m_gbuffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPES::DIFFUSE);
			glBlitFramebuffer(0, 0, width, height,
				0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

			m_gbuffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPES::NORMAL);
			glBlitFramebuffer(0, 0, width, height,
				0, HalfHeight, HalfWidth, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

			m_gbuffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPES::POSITION);
			glBlitFramebuffer(0, 0, width, height,
				HalfWidth, HalfHeight, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

			m_gbuffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPES::UV);
			glBlitFramebuffer(0, 0, width, height,
				HalfWidth, 0, width, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		}
	}

	m_shaderManager.unbindProgram();
	if (window == nullptr)
	{
		OutputDebugString((CPSTR)"RenderSystem Window pointer is null!!!!");
	}
	else
	{
		glfwSwapBuffers(window->getWindow());
	}

}
/*
Qt with regular event loop for editor
Embedded qwindow use qwidget::createwindowcontainer
REnder to this window
SA: replace w/ custom event loop


Qt for editor, glfw for game window for performance
http://stackoverflow.com/questions/12718296/is-there-a-way-to-use-qt-without-qapplicationexec
*/