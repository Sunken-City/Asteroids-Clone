#pragma once
#include "Game/Entity.hpp"

class XInputController;

class Ship : public Entity
{
public:
	Ship(XInputController* controller);
	~Ship();

	void Update(float time);
	void Render() const;
	void Crash();
	void Spawn();
	Vector2 GetNosePosition() const;

private:
	void Thrust();
	void FireWeapon();
	void InitializeVerts();
	void UpdateFromKeyboardControls(float deltaTime);
	void RenderAsDead(float red, float green, float blue) const;

	static const int NUM_SHIP_VERTS = 6;
	static const int NUM_THRUST_VERTS = 4;
	static const int LEFT_THRUST_INDEX = 1;
	static const int RIGHT_THRUST_INDEX = 2;

	static const float SHIP_LENGTH;
	static const float SHIP_WIDTH;
	static const float SHIP_BAR_X;
	static const float SHIP_BAR_Y;
	static const float THRUST_X;
	static const float THRUST_Y;
	static const float THRUST_VARIANCE;
	static const float SHIP_DEATH_ANIM_SECONDS;


	float m_thrustColor;
	Vector2* m_shipVerts[NUM_SHIP_VERTS];
	Vector2* m_thrustVerts[NUM_THRUST_VERTS];
	XInputController* m_controller;
};
