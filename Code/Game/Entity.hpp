#pragma once
#include "Engine/Math/Vector2.hpp"

class Entity
{
public:
	Entity();
	~Entity();
	virtual void Update(float deltaTime);
	virtual void Render() const;
	bool Overlaps(const Entity& ent) const;
	void CheckForScreenWrap();
protected:
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_acceleration;

	float m_angularVelocity;
	float m_orientation;
	float m_physicalRadius;
	float m_cosmeticRadius;
};
