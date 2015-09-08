#include "Game/Asteroid.hpp"

#include <math.h>
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Renderer/TheRenderer.hpp"
#include "Game/TheGame.hpp"
#include "Game/TheApp.hpp"

const float Asteroid::ASTEROID_SPEED = 50.0f;
const float Asteroid::LARGE_ASTEROID_RADIUS = 80.0f;
const float Asteroid::MEDIUM_ASTEROID_RADIUS = LARGE_ASTEROID_RADIUS / 2.f;
const float Asteroid::SMALL_ASTEROID_RADIUS = MEDIUM_ASTEROID_RADIUS / 2.f;
const float Asteroid::LARGE_ASTEROID_BUMP_MAGNITUDE = 10.0f;
const float Asteroid::MEDIUM_ASTEROID_BUMP_MAGNITUDE = LARGE_ASTEROID_BUMP_MAGNITUDE;
const float Asteroid::SMALL_ASTEROID_BUMP_MAGNITUDE = MEDIUM_ASTEROID_BUMP_MAGNITUDE / 2;

Asteroid::Asteroid(AsteroidSize size)
{
	m_isDead = false;
	m_AsteroidSize = size;

	GenerateCosmeticProperties(size);
	SpawnOffscreen();
	InitializeVelocities();
}

Asteroid::Asteroid(AsteroidSize size, const Vector2& spawnPosition)
{
	m_isDead = false;
	m_AsteroidSize = size;

	GenerateCosmeticProperties(size);
	m_position = spawnPosition;
	InitializeVelocities();
}

Asteroid::~Asteroid()
{
	for (int i = 0; i < NUM_SIDES; i++)
	{
		delete verts[i];
	}
}

void Asteroid::Update(float deltaTime)
{
	Entity::Update(deltaTime);
}

void Asteroid::Render() const
{
	TheRenderer::instance->PushMatrix();

	Entity::Render();

	TheRenderer::instance->SetColor(1.f, 1.f, 1.f, 1.f);
	TheRenderer::instance->Translate(m_position.x, m_position.y, 0.0f);
	TheRenderer::instance->Rotate(m_orientation, 0.0f, 0.0f, 1.0f);

	TheRenderer::instance->DrawLineLoop(verts, NUM_SIDES, 2.f);
	TheRenderer::instance->PopMatrix();
}

void Asteroid::GeneratePoints(Vector2 center, float radius, int numSides, float radianOffset, float bumpMagnitude)
{
	const float radiansTotal = 2.0f * MathUtils::pi;
	const float radiansPerSide = radiansTotal / numSides;
	int vertexIndex = 0;

	for (float radians = 0.0f; radians < radiansTotal; radians += radiansPerSide)
	{
		float adjustedRadians = radians + radianOffset;
		float x = center.x + (radius * cos(adjustedRadians) + TheGame::GetRandom(0, static_cast<int>(bumpMagnitude)) - (bumpMagnitude / 2.f));
		float y = center.y + (radius * sin(adjustedRadians) + TheGame::GetRandom(0, static_cast<int>(bumpMagnitude)) - (bumpMagnitude / 2.f));
		verts[vertexIndex++] = new Vector2(x, y);
	}

}

void Asteroid::GenerateCosmeticProperties(AsteroidSize size)
{
	//Assume large to prevent uninitialized variables.
	float asteroidSize = LARGE_ASTEROID_RADIUS;
	float bumpMagnitude = LARGE_ASTEROID_BUMP_MAGNITUDE;
	
	if (size == AsteroidSize::MEDIUM)
	{
		asteroidSize = MEDIUM_ASTEROID_RADIUS;
		bumpMagnitude = MEDIUM_ASTEROID_BUMP_MAGNITUDE;
	}
	else if (size == AsteroidSize::SMALL)
	{
		asteroidSize = SMALL_ASTEROID_RADIUS;
		bumpMagnitude = SMALL_ASTEROID_BUMP_MAGNITUDE;
	}

	m_physicalRadius = asteroidSize;
	m_cosmeticRadius = asteroidSize + (bumpMagnitude / 2.0f);

	GeneratePoints(Vector2(0.0f, 0.0f), static_cast<float>(asteroidSize), NUM_SIDES, 0, bumpMagnitude);
}

void Asteroid::SpawnOffscreen()
{
	const float OUT_OF_BOUNDS_X = TheApp::instance->GetWindowWidth() + m_cosmeticRadius;
	const float OUT_OF_BOUNDS_Y = TheApp::instance->GetWindowHeight() + m_cosmeticRadius;

	if (TheGame::GetRandom(1, 2) == 1)
	{
		m_position = Vector2(OUT_OF_BOUNDS_X, static_cast<float>(TheGame::GetRandom(0, static_cast<int>(TheApp::instance->GetWindowHeight()))));
	}
	else
	{
		m_position = Vector2(static_cast<float>(TheGame::GetRandom(0, static_cast<int>(TheApp::instance->GetWindowWidth()))), OUT_OF_BOUNDS_Y);
	}
}

void Asteroid::InitializeVelocities()
{
	//Pick a random velocity and direction
	m_angularVelocity = (float)TheGame::GetRandom(20, 40) * (TheGame::GetRandom(1, 2) == 1 ? -1.0f : 1.0f);

	int randomDirectionDegrees = TheGame::GetRandom(0, 360);
	m_velocity = Vector2(ASTEROID_SPEED * cos(static_cast<float>(randomDirectionDegrees)), ASTEROID_SPEED * sin(static_cast<float>(randomDirectionDegrees)));
}

AsteroidSize Asteroid::GetAsteroidSize()
{
	return m_AsteroidSize;
}
