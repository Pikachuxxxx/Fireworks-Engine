#include "rigidbody2d.h"

fireworks::physics::RigidBody2D::RigidBody2D(float density, float friction, RigidBodyType bodytype, b2World& world) : components::Component("RigidBody2D", components::ComponentsList::RB2D), bodyType(bodytype), density(1.0f), friction(0.3f), gravityScale(1), fixedRotation(false), resitution(0), m_World(world), m_DidGenerateRB(false), m_Body(nullptr)
{											

}

fireworks::physics::RigidBody2D::~RigidBody2D()
{
	m_World.DestroyBody(m_Body);
}

glm::vec3 fireworks::physics::RigidBody2D::GetPositionInMeters()
{
	b2Vec2 pos = m_Body->GetPosition();
	return glm::vec3(pos.x, pos.y, 0.0f);
}

glm::vec3 fireworks::physics::RigidBody2D::GetPositionInPixels()
{
	b2Vec2 pos = m_Body->GetPosition();
	return glm::vec3(pos.x * M2PX, pos.y * M2PY, 0.0f);
}

float fireworks::physics::RigidBody2D::GetRotation()
{
	return m_Body->GetAngle();
}

void fireworks::physics::RigidBody2D::AddForce(glm::vec2 direction, float force)
{
	m_Body->ApplyForce(b2Vec2(direction.x * force, direction.y * force), m_Body->GetWorldCenter(), true);
}

void fireworks::physics::RigidBody2D::SetVelocity(glm::vec2 velocity)
{
	m_Body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

// FIXME: Set position is not working
void fireworks::physics::RigidBody2D::SetPosition(const glm::vec3& position)
{
	m_BodyDef.position.Set(position.x * P2MX / 2, position.y * P2MY / 2);
}

// FIXME: Set size is not working
void fireworks::physics::RigidBody2D::SetSize(glm::vec2& size)
{
	m_Shape.SetAsBox(size.x * P2MX / 2, size.y * P2MY / 2);
}

// FIXME: Though this is safe from outside tampering this method should not be exposed
void fireworks::physics::RigidBody2D::GenerateRigidBody(glm::vec3 pos, glm::vec2 dim)
{
	if (m_DidGenerateRB)
		return;

	m_World.SetContinuousPhysics(true);
	m_BodyDef.type = (b2BodyType)bodyType;
	m_BodyDef.position.Set(pos.x * P2MX, pos.y * P2MY);
	m_Body = m_World.CreateBody(&m_BodyDef);
	m_Body->SetGravityScale(gravityScale);
	m_Body->SetFixedRotation(fixedRotation);
	m_Shape.SetAsBox(dim.x * P2MX / 2, dim.y * P2MY / 2);
	m_Fixture.shape = &m_Shape;
	m_Fixture.density = density;
	m_Fixture.friction = friction;
	m_Fixture.restitution = resitution;
	m_Body->CreateFixture(&m_Fixture);

	m_DidGenerateRB = true;
}