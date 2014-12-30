#include "GLSim/core/PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() { }
PhysicsSystem::~PhysicsSystem() { }


void PhysicsSystem::update()
{
	sendMessage(MessageUpdatePhysics());
}