#pragma once
#include "Engine/Input/XInputController.hpp"

class Asteroid;
enum class AsteroidSize;
class Ship;
class Bullet;

class TheGame
{
public:
	TheGame();
	~TheGame();
	void Update(float deltaTime);
	void Render();
	void SpawnAsteroidWave();
	void AddAsteroid(AsteroidSize size);
	void AddAsteroid(AsteroidSize size, const Vector2& spawnPosition);
	void SplitAsteroid(Asteroid* asteroid);
	void RemoveAsteroid();
	void SpawnBullet(const Vector2& nosePosition, const Vector2& velocity, float orientation, int factionNumber, float bulletSpeed, float lifespan);

	static int GetRandom(int minimum, int maximum);
	static TheGame* instance;

private:
	static const int INITIAL_ASTEROIDS = 6;
	static const int MAX_ASTEROIDS = 200;
	static const int MAX_SHIPS = XInputController::MAX_CONTROLLERS;
	static const int MAX_BULLETS = 100;

	static Asteroid* m_asteroids[MAX_ASTEROIDS];
	static Ship* m_ships[MAX_SHIPS];
	static Bullet* m_bullets[MAX_BULLETS];
	static XInputController* m_controllers[XInputController::MAX_CONTROLLERS];
	static int m_waveNumber;
	static int m_asteroidCount;

};
