#pragma once

#include <box2d/box2d.h>
#include "../maths/maths.h"
#include "../components/component.h"

/// The Physics World and World Gravity
static const b2Vec2 gravity(0.0f, -10.0f);
static b2World World(gravity);

namespace fireworks { namespace physics { 

	/// Box2D scaling factors (set these up dynamically using the projections matrix's **Aspect Ratio** and Screen coordinate range)
	const double M2PX = 16.0, M2PY = 12.0;
	const double P2MX = (double)1.0 / M2PX, P2MY = (double)1.0 / M2PY;

	
	class RigidBody2D : public components::Component
	{
	public:
		/// Denotes whether the RigidBody2D is dynamic, static or kinematic.
		bool								isDynamic;
		float								density;
		float								friction;
	private:
		b2World&							m_World;
		b2BodyDef							m_BodyDef;
		b2Body*								m_Body;
		b2PolygonShape						m_Shape;
		b2FixtureDef						m_Fixture;

		bool								m_DidGenerateRB;
	public:
		RigidBody2D(float density, float friction, bool dynamic, b2World& world = World);
		~RigidBody2D();

		maths::vec3 GetPositionInMeters();
		maths::vec3 GetPositionInPixels();
		float GetRotation();
		void AddForce(maths::vec2 direction, float force);
		void SetVelocity(maths::vec2 velocity);
		void SetPosition(const maths::vec3& position);
		void SetSize(maths::vec2& size);
		void GenerateRigidBody(maths::vec3 pos, maths::vec2 dim);
	private:
	};

} }