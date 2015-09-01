#pragma once
#include "Game/Entity.hpp"

class Ship : public Entity
{
public:
	Ship();
	~Ship();

	void Update(float time);
	void Render() const;
	void InitializeVerts();
	void DrawDebugCircle(Vector2 center, float radius) const;
	void Crash();
	void Spawn();
	bool IsAlive();
	static void ToggleDebugDraw();

private:
	static const int NUM_VERTS = 10;
	static const int LEFT_THRUST_INDEX = 7;
	static const int RIGHT_THRUST_INDEX = 8;

	static const float SHIP_LENGTH;
	static const float SHIP_WIDTH;
	static const float SHIP_BAR_X;
	static const float SHIP_BAR_Y;
	static const float THRUST_X;
	static const float THRUST_Y;
	static const float THRUST_VARIANCE;

	static bool m_debugInfo;

	bool m_isAlive;

	Vector2* verts[NUM_VERTS];
};
