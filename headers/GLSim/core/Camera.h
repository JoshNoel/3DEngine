#ifndef OGL_CAMERA_INCLUDED
#define OGL_CAMERA_INCLUDED

#include "GLSim/core/Component.h"

namespace ogl { class Camera; }
class Camera : public Component
{
public:
	Camera();
	~Camera();

	void receiveMessage(Message& message);

	inline void setFOV(float fov) { m_fov = fov; }
	inline void setNearPlane(float near) { m_near = near; }
	inline void setFarPlane(float far) { m_far = far; }
	inline void setAR(float ar) { m_ar = ar; }
	inline void setClearColor(glm::vec3 v) { m_clearColor = v; }
	inline void setAmbientColor(glm::vec3 v) { m_ambientColor = v; m_updateCameraUniforms = true; }
	inline void setAmbientIntensity(float v) { m_ambientIntensity = v; m_updateCameraUniforms = true; }


	void render(ShaderManager* manager);

	inline glm::mat4 getPerspective() { return glm::perspective(m_fov, m_ar, m_near, m_far); }
	inline glm::vec3 getClearColor() { return m_clearColor; }

private:
	float m_fov = 45.0f;
	float m_near = 0.1f;
	float m_far = 10000.0f;
	float m_ar = 4.0f / 3.0f;

	float m_ambientIntensity;
	glm::vec3 m_ambientColor;
	bool m_updateCameraUniforms;

	glm::mat4 m_persMat = glm::mat4(1.0f);
	glm::vec3 m_clearColor = glm::vec3(0, 0, 0);
};

#endif