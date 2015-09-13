#include "Game/Bullet.hpp"
#include "Engine/Renderer/TheRenderer.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/MathUtils.hpp"
#include <math.h>

Bullet::Bullet(const Vector2& shipNosePosition, const Vector2& shipVelocity, float shipOrientation, int factionNumber, float bulletSpeed, float lifespan) 
: m_faction(factionNumber)
, m_bulletSpeed(bulletSpeed)
, m_lifespan(lifespan)
{
	m_isDead = false;
	m_orientation = shipOrientation;
	m_angularVelocity = 0.0f;

	m_position = shipNosePosition;
	Vector2 firingVelocity = (Vector2(cos(MathUtils::DegreesToRadians(m_orientation)), sin(MathUtils::DegreesToRadians(m_orientation))) * m_bulletSpeed);
	m_velocity = shipVelocity + firingVelocity;
	m_acceleration = Vector2(0.0f, 0.0f);

	m_cosmeticRadius = 2.0f;
	m_physicalRadius = 2.0f;
}

Bullet::~Bullet()
{

}

void Bullet::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	m_colorTransitionFraction = m_ageInSeconds / m_lifespan;
	if (m_ageInSeconds >= m_lifespan)
	{
		m_isDead = true;
	}
}

void Bullet::Render() const
{
	Entity::Render();
	TheRenderer::instance->SetColor(1.0f, m_colorTransitionFraction, 0.0f, 1.0f);
	TheRenderer::instance->SetPointSize(3);
	TheRenderer::instance->DrawPoint(m_position);
	TheRenderer::instance->SetPointSize(1);
}

int Bullet::GetFaction()
{
	return m_faction;
}
