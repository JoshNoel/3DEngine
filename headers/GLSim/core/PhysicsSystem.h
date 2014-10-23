#ifndef OGL_PHYSICSSYSTEM_INCLUDED
#define OGL_PHYSICSSYSTEM_INCLUDED

#include "GLSim/core/System.h"

#include "GLSim/core/Object.h"

namespace ogl { class PhysicsSystem; }
class PhysicsSystem : public System
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void update();
private:
};

#endif