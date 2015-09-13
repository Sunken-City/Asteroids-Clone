#include "Game/TheGame.hpp"
#include <stdlib.h>
#include "Game/Asteroid.hpp"
#include "Game/Ship.hpp"
#include "Game/TheApp.hpp"
#include "Game/Bullet.hpp"

TheGame* TheGame::instance = nullptr;
Asteroid* TheGame::m_asteroids[MAX_ASTEROIDS];
Ship* TheGame::m_ships[MAX_SHIPS];
Bullet* TheGame::m_bullets[MAX_BULLETS];
XInputController* TheGame::m_controllers[XInputController::MAX_CONTROLLERS];
int TheGame::m_waveNumber = 0;
int TheGame::m_asteroidCount = TheGame::INITIAL_ASTEROIDS;

TheGame::TheGame()
{
	srand(0xDEADBEEF);

	for (int i = 0; i < XInputController::MAX_CONTROLLERS; i++)
	{
		m_controllers[i] = new XInputController(i);
	}
	for (int i = 0; i < INITIAL_ASTEROIDS; i++)
	{
		m_asteroids[i] = new Asteroid(AsteroidSize::LARGE);
	}
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		m_bullets[i] = nullptr;
	}

	//Spawn the first ship by default, then add other ships if we have controllers connected for them.
	m_ships[0] = new Ship(m_controllers[0]);
	for (int i = 1; i < MAX_SHIPS; i++)
	{
		if (m_controllers[i]->IsConnected())
		{
			m_ships[i] = new Ship(m_controllers[i]);
		}
		else
		{
			m_ships[i] = nullptr;
		}
	}
}

TheGame::~TheGame()
{
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		if (m_asteroids[i] != nullptr)
		{
			delete m_asteroids[i];
		}
	}
	for (int i = 0; i < MAX_SHIPS; i++)
	{
		if (m_ships[i] != nullptr)
		{
			delete m_ships[i];
		}
	}
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (m_bullets[i] != nullptr)
		{
			delete m_bullets[i];
		}
	}
	for (int i = 0; i < XInputController::MAX_CONTROLLERS; i++)
	{
		delete m_controllers[i];
	}
}

int TheGame::GetRandom(int minimum, int maximum)
{
	return rand() % maximum + minimum;
}

void TheGame::SpawnBullet(const Vector2& nosePosition, const Vector2& velocity, float orientation, int factionNumber, float bulletSpeed, float lifespan)
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (m_bullets[i] == nullptr)
		{
			m_bullets[i] = new Bullet(nosePosition, velocity, orientation, factionNumber, bulletSpeed, lifespan);
			return;
		}
	}
}

void TheGame::AddAsteroid(AsteroidSize size)
{
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		if (m_asteroids[i] == nullptr)
		{
			m_asteroids[i] = new Asteroid(size);
			m_asteroidCount++;
			return;
		}
	}
}

void TheGame::AddAsteroid(AsteroidSize size, const Vector2& spawnPosition)
{
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		if (m_asteroids[i] == nullptr)
		{
			m_asteroids[i] = new Asteroid(size, spawnPosition);
			m_asteroidCount++;
			return;
		}
	}
}

void TheGame::SplitAsteroid(Asteroid* asteroid)
{
	AsteroidSize size = asteroid->GetAsteroidSize();
	Vector2 spawnLocation = asteroid->GetPosition();
	if (size == AsteroidSize::LARGE)
	{
		AddAsteroid(AsteroidSize::MEDIUM, spawnLocation);
		AddAsteroid(AsteroidSize::MEDIUM, spawnLocation);
	}
	else if (size == AsteroidSize::MEDIUM)
	{
		AddAsteroid(AsteroidSize::SMALL, spawnLocation);
		AddAsteroid(AsteroidSize::SMALL, spawnLocation);
	}
}

void TheGame::RemoveAsteroid()
{
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		if (m_asteroids[i] != nullptr)
		{
			delete m_asteroids[i];
			m_asteroids[i] = nullptr;
			m_asteroidCount--;
			return;
		}
	}
}

void TheGame::Update(float deltaTime)
{
	for (int i = 0; i < XInputController::MAX_CONTROLLERS; i++)
	{
		m_controllers[i]->Update(deltaTime);
	}

	//Spawn a new ship per controller we add. Delete them if the controller is removed.
	for (int i = 1; i < MAX_SHIPS; i++)
	{
		bool connected = m_controllers[i]->IsConnected();
		if (connected && m_ships[i] == nullptr)
		{
			m_ships[i] = new Ship(m_controllers[i]);
		}
		if (!connected && m_ships[i] != nullptr)
		{
			delete m_ships[i];
			m_ships[i] = nullptr;
		}
	}

	for (int i = 0; i < MAX_SHIPS; i++)
	{
		if (m_ships[i] != nullptr)
		{
			m_ships[i]->Update(deltaTime);
		}
	}
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (m_bullets[i] != nullptr)
		{
			m_bullets[i]->Update(deltaTime);
			if (m_bullets[i]->IsDead())
			{
				m_bullets[i] = nullptr;
			}
		}
	}
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		if (m_asteroids[i] != nullptr)
		{
			m_asteroids[i]->Update(deltaTime);

			//Test for collisions of each of the asteroids against each of the ships
			for (int j = 0; j < MAX_SHIPS; j++)
			{
				if (m_ships[j] != nullptr && !m_ships[j]->IsDead() && m_asteroids[i] != nullptr && m_ships[j]->Overlaps(*m_asteroids[i]))
				{
					SplitAsteroid(m_asteroids[i]);
					delete m_asteroids[i];
					m_ships[j]->Crash();
					m_asteroids[i] = nullptr;
					m_asteroidCount--;
				}
			}

			//Test for collisions of each of the asteroids against each of the bullets
			for (int k = 0; k < MAX_BULLETS; k++)
			{
				if (m_bullets[k] != nullptr && m_asteroids[i] != nullptr && m_bullets[k]->Overlaps(*m_asteroids[i]))
				{
					SplitAsteroid(m_asteroids[i]);
					delete m_asteroids[i];
					delete m_bullets[k];
					m_asteroids[i] = nullptr;
					m_bullets[k] = nullptr;
					m_asteroidCount--;
				}
			}
		}
	}

	if (TheApp::instance->IsKeyDown('P'))
	{
		if (m_ships[0] != nullptr)
		{
			m_ships[0]->Spawn();
		}
	}

	if (TheApp::instance->WasKeyJustPressed('L'))
	{
		RemoveAsteroid();
	}

	if (TheApp::instance->WasKeyJustPressed('O'))
	{
		AddAsteroid(AsteroidSize::LARGE);
	}

	if (TheApp::instance->WasKeyJustPressed('G'))
	{
		Entity::ToggleDebugDraw();
	}

	if (m_asteroidCount <= 0)
	{
		SpawnAsteroidWave();
	}
}

void TheGame::Render()
{
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		if (m_asteroids[i] != nullptr)
		{
			m_asteroids[i]->Render();
		}
	}
	for (int i = 0; i < MAX_SHIPS; i++)
	{
		if (m_ships[i] != nullptr)
		{
			m_ships[i]->Render();
		}
	}
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (m_bullets[i] != nullptr)
		{
			m_bullets[i]->Render();
		}
	}
}

void TheGame::SpawnAsteroidWave()
{
	m_waveNumber++;
	int numAsteroidsToSpawn = INITIAL_ASTEROIDS + m_waveNumber;

	//If we have so many asteroids on screen that we can't split them without running out of asteroid slots, cap the number.
	if (numAsteroidsToSpawn >= MAX_ASTEROIDS / 4)
	{
		numAsteroidsToSpawn = (MAX_ASTEROIDS / 4);
	}
	for (int i = 0; i < numAsteroidsToSpawn; i++)
	{
		AddAsteroid(AsteroidSize::LARGE);
	}
}
