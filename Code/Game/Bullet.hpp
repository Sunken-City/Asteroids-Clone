#pragma once
#include "Game/Entity.hpp"

class Vector2;

class Bullet : public Entity
{
public:
	Bullet(const Vector2& spawnPosition, const Vector2& shipVelocity, float shipOrientation, int factionNumber, float bulletSpeed, float lifespan);
	~Bullet();

	void Update(float deltaTime);
	void Render() const;

	int GetFaction();

private:
	int m_faction;
	float m_bulletSpeed;
	float m_colorTransitionFraction;
	float m_lifespan;
};