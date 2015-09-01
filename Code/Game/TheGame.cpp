#include "Game/TheGame.hpp"
#include <stdlib.h>
#include "Game/Asteroid.hpp"
#include "Game/Ship.hpp"
#include "Game/TheApp.hpp"

TheGame* TheGame::instance = nullptr;
Asteroid* TheGame::m_asteroids[MAX_ASTEROIDS];
Ship* TheGame::m_ships[MAX_SHIPS];

TheGame::TheGame() : m_timeSinceLastPress(1.0f)
{
	srand(0xDEADBEEF);

	for (int i = 0; i < INITIAL_ASTEROIDS; i++)
	{
		m_asteroids[i] = new Asteroid();
	}
	for (int i = 0; i < MAX_SHIPS; i++)
	{
		m_ships[i] = new Ship();
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
}

int TheGame::GetRandom(int minimum, int maximum)
{
	return rand() % maximum + minimum;
}

void TheGame::AddAsteroid()
{
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		if (m_asteroids[i] == nullptr)
		{
			m_asteroids[i] = new Asteroid();
			return;
		}
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
			return;
		}
	}
}

void TheGame::Update(float deltaTime)
{
	for (int i = 0; i < MAX_SHIPS; i++)
	{
		if (m_ships[i] != nullptr)
		{
			m_ships[i]->Update(deltaTime);
		}
	}
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		if (m_asteroids[i] != nullptr)
		{
			m_asteroids[i]->Update(deltaTime);

			for (int j = 0; j < MAX_SHIPS; j++)
			{
				if (m_ships[j] != nullptr && m_ships[j]->IsAlive() && m_ships[j]->Overlaps(*m_asteroids[i]))
				{
					delete m_asteroids[i];
					m_ships[j]->Crash();
					m_asteroids[i] = nullptr;
				}
			}
		}
	}

	if (TheApp::instance->isKeyDown('P'))
	{
		for (int i = 0; i < MAX_SHIPS; i++)
		{
			if (m_ships[i] != nullptr)
			{
				m_ships[i]->Spawn();
			}
		}
	}

	m_timeSinceLastPress += deltaTime;

	if (TheApp::instance->isKeyDown('L') && m_timeSinceLastPress > 0.2f)
	{
		RemoveAsteroid();
		m_timeSinceLastPress = 0.0f;
	}

	if (TheApp::instance->isKeyDown('O') && m_timeSinceLastPress > 0.2f)
	{
		AddAsteroid();
		m_timeSinceLastPress = 0.0f;
	}

	if (TheApp::instance->isKeyDown('G') && m_timeSinceLastPress > 0.2f)
	{
		Asteroid::ToggleDebugDraw();
		Ship::ToggleDebugDraw();
		m_timeSinceLastPress = 0.0f;
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
}
