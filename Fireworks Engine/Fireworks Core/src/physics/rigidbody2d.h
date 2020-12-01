#pragma once

#include <box2d/box2d.h>
#include "../maths/maths.h"
#include "../components/component.h"

/// The Physics World and World Gravity
static const b2Vec2 gravity(0.0f, -10.0f);
static b2World World(gravity);

namespace fireworks { namespace physics { 

	/// Box2D scaling factors (set these up dynamically using the projections matrix's **Aspect Ratio** and Screen coordinate range)
	const double M2PX = 250, M2PY = 150;
	const double P2MX = (double)1.0 / M2PX, P2MY = (double)1.0 / M2PY;

	/// The type of the rigid body
	enum RigidBodyType
	{
		Static = b2_staticBody,
		Dynamic = b2_dynamicBody,
		Kinematic = b2_kinematicBody
	};
	
	/// RigidBody 2D Physics component to simulate real time physics
	class RigidBody2D : public components::Component
	{
	public:
		/// Denotes whether the RigidBody2D is dynamic, static or kinematic.
		RigidBodyType						bodyType;
		/// The density of the rigid body
		float								density;
		/// The friction of the rigid body surface
		float								friction;
		/// The bounciness of the rigid body
		float								resitution;
		/// The effect of gravity on the rigid body
		float								gravityScale;
		/// Whether or not to clamp the rigid bodys rotation
		bool								fixedRotation;
	private:
		b2World&							m_World;
		b2BodyDef							m_BodyDef;
		b2Body*								m_Body;
		b2PolygonShape						m_Shape;
		b2FixtureDef						m_Fixture;

		bool								m_DidGenerateRB;
	public:
		/// Creates the rigid body 
		/// 
		/// @param density The density of the body
		/// @param friction The friction of the rigid body surface
		/// @param bodytype The type of rigid body 
		/// @see physics::RigidBodyType for available types of rigid bodies
		RigidBody2D(float density, float friction, RigidBodyType bodytype, b2World& world = World);
		~RigidBody2D();

		/// Gets the position of the rigid body in meters (M.K.S system) 
		maths::vec3 GetPositionInMeters();
		/// Gets the position of the rigid body in pixels
		maths::vec3 GetPositionInPixels();
		/// Gets the rotation of the rigid body in radians
		/// 
		/// @attention The angle is in radians by default
		float GetRotation();

		/// Applies force to the rigid body
		/// 
		/// @param direction The direction in which to apply force to the rigid body
		/// @param force The magnitude of the force to apply
		void AddForce(maths::vec2 direction, float force);
		/// Sets the velocity of the rigid body
		/// 
		/// @param velocity A 2D velocity vector 
		void SetVelocity(maths::vec2 velocity);
		/// Sets the position of the rigid body
		/// 
		/// @warning This method doesn't work yet
		void SetPosition(const maths::vec3& position);
		/// Sets the size of the rigid body
		/// 
		/// @warning This method doesn't work yet
		void SetSize(maths::vec2& size);
		/// Generates a plane rigid body using the position and dimensions
		void GenerateRigidBody(maths::vec3 pos, maths::vec2 dim);

		/// Gets the box2D body of the rigid body
		inline b2Body* GetBody() { return  m_Body; }
	};

} }