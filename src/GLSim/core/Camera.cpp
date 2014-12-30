#include "GLSim/core/Camera.h"

Camera::Camera()
	: Component(COMPONENT_TYPE::CAMERA)
{
}

Camera::~Camera()
{

}

void Camera::render(ShaderManager* manager)
{
	glm::mat4 perspective = glm::perspective(m_fov, m_ar, m_near, m_far);
	//manager->setUniform("persMatrix", perspective);
	/*glm::mat4 view2 = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0));*/

	if(m_updateCameraUniforms)
	{
		m_updateCameraUniforms = false;
		manager->setUniform("camera.ambientIntensity", m_ambientIntensity);
		manager->setUniform("camera.ambientColor", m_ambientColor);
	}

}

void Camera::receiveMessage(Message& message)
{
	switch(message.getType())
	{
	case Message::RENDER:
		render(static_cast<MessageRender&>(message).getShaderManager());
	default:
		break;
	}
}
