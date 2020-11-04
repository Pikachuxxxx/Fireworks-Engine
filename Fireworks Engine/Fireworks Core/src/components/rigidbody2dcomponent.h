#pragma once

#include <string>

#include "component.h"

// Forward declaration of the respective component
namespace fireworks { namespace  physics {
	class RigidBody2D;
} }

namespace fireworks { namespace graphics {
	class Sprite;
} }

namespace fireworks { namespace  components {

	class RigidBody2DComponent : public Component
	{
	public:
		physics::RigidBody2D* m_RigidBody2D;
	public:
		RigidBody2DComponent(physics::RigidBody2D* rigidbody2d);

		inline void SetComponentType(const std::string& componentName, unsigned int componentID) override;
	};

	
} }