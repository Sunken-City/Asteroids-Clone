#pragma once
#include "Game/Entity.hpp"

 class Asteroid : public Entity
 {
 public:
	 Asteroid();
	 ~Asteroid();

	 void Update(float deltaTime);
	 void Render() const;

	 static void ToggleDebugDraw();

 private:
	 void GeneratePoints(Vector2 center, float radius, int numSides, float radianOffset);
	 void DrawDebugCircle(Vector2 center, float radius) const;

	 static const int NUM_SIDES = 48;
	 static const int ASTEROID_BUMP_MAGNITUDE = 10;
	 static const int ASTEROID_RADIUS = 35;
	 static bool m_debugInfo;

	 Vector2* verts[NUM_SIDES];
 };
