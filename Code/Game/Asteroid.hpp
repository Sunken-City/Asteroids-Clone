#pragma once
#include "Game/Entity.hpp"

enum class AsteroidSize
{
	LARGE,
	MEDIUM,
	SMALL
};

 class Asteroid : public Entity
 {
 public:
	 Asteroid(AsteroidSize size);
	 Asteroid(AsteroidSize size, const Vector2& spawnPosition);
	 ~Asteroid();

	 void Update(float deltaTime);
	 void Render() const;
	 AsteroidSize GetAsteroidSize();

 private:
	 void GeneratePoints(Vector2 center, float radius, int numSides, float radianOffset, float bumpMagnitude);
	 void GenerateCosmeticProperties(AsteroidSize size);
	 void SpawnOffscreen();
	 void InitializeVelocities();
	 static const int NUM_SIDES = 48;

	 static const float LARGE_ASTEROID_BUMP_MAGNITUDE;
	 static const float MEDIUM_ASTEROID_BUMP_MAGNITUDE;
	 static const float SMALL_ASTEROID_BUMP_MAGNITUDE;

	 static const float LARGE_ASTEROID_RADIUS;
	 static const float MEDIUM_ASTEROID_RADIUS;
	 static const float SMALL_ASTEROID_RADIUS;

	 static const float ASTEROID_SPEED;

	 Vector2* verts[NUM_SIDES];
	 AsteroidSize m_AsteroidSize;
 };
