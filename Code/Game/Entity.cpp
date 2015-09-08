#include "Game/Entity.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Game/TheApp.hpp"
#include "Engine/Renderer/TheRenderer.hpp"
#include <math.h>

bool Entity::m_displayDebugInfo = false;

Entity::Entity()
: m_position(Vector2(0.0f, 0.0f))
, m_velocity(Vector2(0.0f, 0.0f))
, m_acceleration(Vector2(0.0f, 0.0f))
, m_orientation(0.0f)
, m_angularVelocity(0.0f)
, m_ageInSeconds(0.0f)
, m_isDead(true)
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
	m_ageInSeconds += deltaTime;
	CheckForScreenWrap();
}

void Entity::Render() const
{
	if (m_displayDebugInfo)
	{
		TheRenderer::instance->SetColor(0.0f, 1.0f, 1.0f, 1.0f);

		TheRenderer::instance->SetPointSize(3);
		TheRenderer::instance->DrawPoint(m_position);
		TheRenderer::instance->SetPointSize(1);

		TheRenderer::instance->SetColor(1.0f, 1.0f, 0.0f, 1.0f);
		Vector2 orientation = m_position + Vector2(cos(MathUtils::DegreesToRadians(m_orientation)), sin(MathUtils::DegreesToRadians(m_orientation))) * 10.0f;
		TheRenderer::instance->DrawLine(m_position, orientation, 1.f);

		TheRenderer::instance->SetColor(0.0f, 1.0f, 0.0f, 1.0f);
		TheRenderer::instance->DrawPolygonOutline(m_position, m_cosmeticRadius, TheRenderer::CIRCLE_SIDES, 0.0f);

		TheRenderer::instance->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		TheRenderer::instance->DrawPolygonOutline(m_position, m_physicalRadius, TheRenderer::CIRCLE_SIDES, 0.0f);

		TheRenderer::instance->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
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

Vector2 Entity::GetPosition()
{
	return m_position;
}

Vector2 Entity::GetVelocity()
{
	return m_velocity;
}

float Entity::GetOrientation()
{
	return m_orientation;
}

bool Entity::IsDead()
{
	return m_isDead;
}

void Entity::ToggleDebugDraw()
{
	m_displayDebugInfo = !m_displayDebugInfo;
}