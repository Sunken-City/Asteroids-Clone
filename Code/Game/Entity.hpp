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
	Vector2 GetPosition();
	Vector2 GetVelocity();
	float GetOrientation();
	bool IsDead();

	static void ToggleDebugDraw();

protected:
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_acceleration;

	float m_angularVelocity;
	float m_orientation;
	float m_physicalRadius;
	float m_cosmeticRadius;
	float m_ageInSeconds;
	float m_ageAtDeath;

	bool m_isDead;

	static bool m_displayDebugInfo;
};
