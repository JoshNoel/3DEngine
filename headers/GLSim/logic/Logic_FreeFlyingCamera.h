#ifndef OGL_LOGIC_FREEFLYINGCAMERA_INCLUDED
#define OGL_LOGIC_FREEFLYINGCAMERA_INCLUDED

#include "GLSim/core/Logic.h"

namespace ogl { class Logic_FreeFlyingCamera; }
class Logic_FreeFlyingCamera : public Logic
{
public:
	Logic_FreeFlyingCamera();
	~Logic_FreeFlyingCamera();

	void receiveMessage(Message&);


private:
	void update();

//Data
private:
	float m_moveSpeed = 0.00005f;
	float m_mouseSens = 0.1f;
};


#endif
