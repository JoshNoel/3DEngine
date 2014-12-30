#include "GLSim/core/RenderSystem.h"
#include "GLSim/core/Transform.h"
#include <Windows.h>

RenderSystem::RenderSystem(bool shouldDefer)
	:m_shaderManager(),
	m_deferred(shouldDefer)
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
		if(!m_shaderManager.addShader(ShaderManager::SHADER_TYPE::VERTEX, "C:/Projects/3DSim/res/shaders/BasicDeferredVertex.vs", 0))
			fprintf(stdout, "Error adding Vertex Shader\n");
		if(!m_shaderManager.addShader(ShaderManager::SHADER_TYPE::FRAGMENT, "C:/Projects/3DSim/res/shaders/BasicDeferredFragment.fs", 0))
			fprintf(stdout, "Error adding Fragment Shader\n");
	}

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
	if(p_camera)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_shaderManager.useProgram(0);

		/*glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 12*3);
		glDisableVertexAttribArray(0);*/
		p_camera->getComponent<Transform>()->receiveMessage(MessageRender(interp, &m_shaderManager, glm::mat4(1.0), false));
		p_camera->getComponent<Camera>()->receiveMessage(MessageRender(interp, &m_shaderManager, glm::mat4(1.0), false));
		//Transform* t = p_camera->getComponent<Transform>().get();
		//glm::mat4 view = glm::lookAt(t->getPosition(), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		Transform* cam = p_camera->getComponent<Transform>();
		//glm::mat4 view = cam->getTranslationMat()._inverse() * cam->getRotationMat();
		glm::mat4 view = glm::inverse(cam->getTranslationMat() * cam->getRotationMat());//glm::lookAt(cam->getPosition(), cam->getForward(), cam->getUp());
		/*glm::mat4 t = cam->getRotationMat();
		fprintf(stdout, "(%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)\n",
			t[0][0], t[0][1], t[0][2], t[0][3],
			t[1][0], t[1][1], t[1][2], t[1][3],
			t[2][0], t[2][1], t[2][2], t[2][3],
			t[3][0], t[3][1], t[3][2], t[3][3]);*/
		//fprintf(stdout, "(%d, %d, %d) || (%d, %d, %d)\n", cam->getPosition().x, cam->getPosition().y, cam->getPosition().z, cam->getOrientation().x, cam->getOrientation().y, cam->getOrientation().z);
		//glm::mat4 v2 = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		/*sendMessage(MessageRender(interp, &m_shaderManager, p_camera->getComponent<Camera>()->getPerspective() *
			p_camera->getComponent<Transform>()->getModelNoScale(), true));*/

		//m_shaderManager.setUniform("MVP", p_camera->getComponent<Camera>()->getPerspective() * glm::translate(glm::vec3(0, 0, -6)));

		//m_shaderManager.setUniform("M", glm::mat4());

		
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

	m_shaderManager.unbindProgram();
	if (window == nullptr)
	{
		OutputDebugString((LPCSTR)"RenderSystem Window pointer is null!!!!");
	}
	else
	{
		glfwSwapBuffers(window->getWindow());
	}
}
/*Qt with regular event loop for editor
Embedded qwindow use qwidget::createwindowcontainer
REnder to this window
SA: replace w/ custom event loop
http://stackoverflow.com/questions/12718296/is-there-a-way-to-use-qt-without-qapplicationexec













*/