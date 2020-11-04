#include "rigidbody2dcomponent.h"

fireworks::components::RigidBody2DComponent::RigidBody2DComponent(physics::RigidBody2D* rigidbody2d)
	: m_RigidBody2D(rigidbody2d)
{
	SetComponentType("RidigBody2D", Components::RB2D);
}

void fireworks::components::RigidBody2DComponent::SetComponentType(const std::string& componentName, unsigned int componentID)
{
	componentType.name = componentName;
	componentType.typeID = componentID;
}
