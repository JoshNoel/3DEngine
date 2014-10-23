#include "GLSim/core/Transform.h"
#include "glm/gtx/quaternion.hpp"

Transform::Transform()
	: Component(COMPONENT_TYPE::TRANSFORM),
	m_orientation(0,0,0,1),
	m_position(0,0,0),
	m_scale(1, 1, 1),
	m_model(1),
	m_translationMat(1),
	m_rotationMat(1),
	m_scaleMat(1),
	m_forward(0,0,-1),
	m_up(0,1,0),
	m_lastOrientation(0,0,0,1),
	m_lastPosition(0,0,0),
	m_lastScale(1, 1, 1),
	m_cameraMode(false)
{

}

Transform::~Transform()
{

}

glm::fquat Transform::lookAt(const glm::vec3& dest, const glm::vec3& up)
{
	//glm::vec3 nSource = glm::normalize(m_position);
	//glm::vec3 nDest = glm::normalize(dest);

	float dot = glm::dot(m_position, dest);

	if(std::abs(dot - (-1.0f)) < 0.000001f)
	{
		return glm::angleAxis(180.0f, up);
	}

	if(std::abs(dot - (1.0f)) < 0.000001f)
	{
		return glm::fquat(0.0f, 0.0f, 0.0f, 1.0f);
	}

	float angle = acosf(dot);
	glm::vec3 axis = glm::cross(m_position, dest);
	return glm::angleAxis(angle, axis);	
}

void Transform::receiveMessage(Message& m)
{
	switch(m.getType())
	{
	case Message::RENDER:
	{
		MessageRender& r = static_cast<MessageRender&>(m);
		render(r.getInterp(), r.getShaderManager(), r.getVP(), r.shouldSetMVP());
	}
	break;
	case Message::STEP_PHYSICS:
		updatePhysics();
		break;
	}
}

void Transform::render(float interp, ShaderManager* manager, glm::mat4 VP, bool setMVP)
{
	glm::fquat q = glm::mix(m_lastOrientation, m_orientation, interp);
	glm::vec3 pos = glm::lerp<float>(m_lastPosition, m_position, interp);
	glm::vec3 s = glm::lerp<float>(m_lastScale, m_scale, interp);


	m_rotationMat = glm::toMat4(q);

	m_translationMat = glm::translate(pos);

	//if(m_orientation != m_lastOrientation)


	m_scaleMat = glm::scale(s);

	m_forward = glm::vec3(glm::vec4(m_forward, 1.0) * m_rotationMat);
	//m_up = glm::vec3(glm::vec4(m_up, 1.0) * m_rotationMat);

	if(m_cameraMode)
		m_model = m_translationMat * m_rotationMat;
	else
		m_model = m_translationMat * m_rotationMat * m_scaleMat;

	if(setMVP && !m_cameraMode)
		manager->setUniform("MVP", VP * m_model);
	
	manager->setUniform("M", m_model);
	//* model);
	/*glm::mat4 view = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0));
	//manager->setUniform("viewMatrix", model);
	glm::mat4 perspective = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	//manager->setUniform("persMatrix", perspective);
	glm::mat4 MVP = perspective * view * model;*/
	//manager->setUniform("MVP", MVP);

}

void Transform::updatePhysics()
{
	m_lastOrientation = m_orientation;
	m_lastPosition = m_position;
	m_lastScale = m_scale;
}

void Transform::translate(const glm::vec3& v)
{
	m_position += glm::vec3(m_orientation * glm::vec4(v, 1));
}

void Transform::rotate(const glm::vec3& axis, float angle)
{
	//glm::vec3 a = glm::vec3(m_orientation * glm::vec4(axis, 1));
	if(axis == glm::vec3(0,1,0) && m_cameraMode)
		m_orientation = glm::normalize(glm::angleAxis(angle, axis)) * m_orientation;
	else
		m_orientation = m_orientation * glm::normalize(glm::angleAxis(angle, axis));
	glm::normalize(m_orientation);
}

void Transform::scale(const glm::vec3& v)
{
	m_scale *= v;
}

void Transform::setPosition(const glm::vec3& v)
{
	m_lastPosition = v;
	m_position = v;
}

void Transform::setScale(const glm::vec3& v)
{
	m_lastScale = v;
	m_scale = v;
}