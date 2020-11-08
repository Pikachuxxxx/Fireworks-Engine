#pragma once

#include <box2d/box2d.h>

//namespace fireworks { namespace managers { 

	/// A singleton Physics Manager.
	/// 
	/// Manages the Physics world and the Physics simulation properties in a global scope.
	class PhysicsManager
	{
	public:
		b2Vec2		Gravity;
		b2World*	PhysicsWorld;
	private:
		static PhysicsManager* m_PhysicsManager;
	private:
		PhysicsManager()
		{
			Gravity = b2Vec2(0.0f, -9.81f);
			PhysicsWorld = new b2World(Gravity);
			if (!m_PhysicsManager)
			{
				m_PhysicsManager = new PhysicsManager();
			}
		}

	};

//} }