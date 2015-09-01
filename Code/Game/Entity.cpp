#include "Game/Entity.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Game/TheApp.hpp"


Entity::Entity() : m_position(Vector2(0.0f, 0.0f)), m_velocity(Vector2(0.0f, 0.0f)), m_acceleration(Vector2(0.0f, 0.0f)), m_orientation(0.0f), m_angularVelocity(0.0f)
{
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{
	m_velocity += m_acceleration * deltaTime;
	m_position += m_velocity * deltaTime;
	m_orientation += m_angularVelocity * deltaTime;
	CheckForScreenWrap();
}

void Entity::Render() const
{

}

bool Entity::Overlaps(const Entity& ent) const
{
	return MathUtils::DoDiscsOverlap(this->m_position, this->m_physicalRadius, ent.m_position, ent.m_physicalRadius);
}

void Entity::CheckForScreenWrap()
{
	if (m_position.x < 0.0f - m_cosmeticRadius)
	{
		m_position.x = TheApp::instance->GetWindowWidth() + m_cosmeticRadius;
	}
	else if (m_position.x > TheApp::instance->GetWindowWidth() + m_cosmeticRadius)
	{
		m_position.x = 0.0f - m_cosmeticRadius;
	}

	if (m_position.y < 0.0f - m_cosmeticRadius)
	{
		m_position.y = TheApp::instance->GetWindowHeight() + m_cosmeticRadius;
	}
	else if (m_position.y > TheApp::instance->GetWindowHeight() + m_cosmeticRadius)
	{
		m_position.y = 0.0f - m_cosmeticRadius;
	}
}
