#pragma once

class Asteroid;
class Ship;

class TheGame
{
public:
	TheGame();
	~TheGame();
	void Update(float deltaTime);
	void Render();
	void AddAsteroid();
	void RemoveAsteroid();

	static int GetRandom(int minimum, int maximum);

	static TheGame* instance;

private:
	static const int INITIAL_ASTEROIDS = 6;
	static const int MAX_ASTEROIDS = 20;
	static const int MAX_SHIPS = 1;

	static Asteroid* m_asteroids[MAX_ASTEROIDS];
	static Ship* m_ships[MAX_SHIPS];
	float m_timeSinceLastPress;
};
