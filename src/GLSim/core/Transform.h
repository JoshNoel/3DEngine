#ifndef OGL_TRANSFORM_INCLUDED
#define OGL_TRANSFORM_INCLUDED

#include "GLSim/core/Component.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "GLSim/core/shadermanager.h"

namespace ogl { class Transform; }
class Transform : public Component
{
public:
	Transform();
	~Transform();

	void receiveMessage(Message&);

	void updatePhysics();
	void render(float interp, ShaderManager* manager, glm::mat4, bool);

	void translate(const glm::vec3&);

	void rotate(const glm::vec3& axis, float angle);

	void scale(const glm::vec3&);

	void setPosition(const glm::vec3&);
	void setScale(const glm::vec3& scale);
	inline void setCameraMode(bool b){ m_cameraMode = b; }


	inline glm::vec3 getPosition() { return m_position; }
	inline glm::vec3 getForward() { return m_forward; }
	inline glm::vec3 getUp() { return m_up; }

	inline glm::fquat getOrientation() { return m_orientation; }
	inline glm::vec3 getScale() { return m_scale; }
	inline glm::mat4 getModel() { return m_model; }
	inline glm::mat4 getTranslationMat() { return m_translationMat; }
	inline glm::mat4 getRotationMat() { return m_rotationMat; }
	inline glm::mat4 getScaleMat() { return m_scaleMat; }

	glm::fquat lookAt(const glm::vec3& dest, const glm::vec3& up);

protected:
	glm::fquat m_orientation;
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::mat4 m_model;
	glm::mat4 m_translationMat;
	glm::mat4 m_rotationMat;
	glm::mat4 m_scaleMat;
	glm::vec3 m_forward;
	glm::vec3 m_up;

private:
	glm::fquat m_lastOrientation;
	glm::vec3 m_lastPosition;
	glm::vec3 m_lastScale;
	bool m_cameraMode;
};
#endif