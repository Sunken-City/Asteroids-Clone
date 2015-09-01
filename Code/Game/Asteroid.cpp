#include "Game/Asteroid.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#include <math.h>

#include "Engine/Math/MathUtils.hpp"
#include "Game/TheGame.hpp"
#include "Game/TheApp.hpp"

bool Asteroid::m_debugInfo = false;

Asteroid::Asteroid()
{
	const float ASTEROID_SPEED = 50.0f;
	const float ASTEROID_COSMETIC_RADIUS = ASTEROID_RADIUS + ASTEROID_BUMP_MAGNITUDE / 2.0f;
	const float OUT_OF_BOUNDS_X = TheApp::instance->GetWindowWidth() + ASTEROID_COSMETIC_RADIUS;
	const float OUT_OF_BOUNDS_Y = TheApp::instance->GetWindowHeight() + ASTEROID_COSMETIC_RADIUS;


	m_physicalRadius = ASTEROID_RADIUS;
	m_cosmeticRadius = ASTEROID_COSMETIC_RADIUS;


	if (TheGame::GetRandom(1, 2) == 1)
	{
		m_position = Vector2(OUT_OF_BOUNDS_X, static_cast<float>(TheGame::GetRandom(0, static_cast<int>(TheApp::instance->GetWindowHeight()))));
	}
	else
	{
		m_position = Vector2(static_cast<float>(TheGame::GetRandom(0, static_cast<int>(TheApp::instance->GetWindowWidth()))), OUT_OF_BOUNDS_Y);
	}

	GeneratePoints(Vector2(0.0f, 0.0f), static_cast<float>(ASTEROID_RADIUS), NUM_SIDES, 0);

	//Pick a random velocity and direction
	m_angularVelocity = (float)TheGame::GetRandom(20, 40) * (TheGame::GetRandom(1, 2) == 1 ? -1.0f : 1.0f);

	int randomDirectionDegrees = TheGame::GetRandom(0, 360);
	m_velocity = Vector2(ASTEROID_SPEED * cos(static_cast<float>(randomDirectionDegrees)), ASTEROID_SPEED * sin(static_cast<float>(randomDirectionDegrees)));
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
	glPushMatrix();

	if (m_debugInfo)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		glBegin(GL_POINTS);
		{
			glVertex2f(m_position.x, m_position.y);
		}
		glEnd();
		glColor3f(0.0f, 1.0f, 0.0f);
		DrawDebugCircle(m_position, m_cosmeticRadius);
		glColor3f(1.0f, 0.0f, 0.0f);
		DrawDebugCircle(m_position, m_physicalRadius);
		glColor3f(1.0f, 1.0f, 1.0f);
	}

	glTranslatef(m_position.x, m_position.y, 0.0f);
	glRotatef(m_orientation, 0.0f, 0.0f, 1.0f);

	glBegin(GL_LINE_LOOP);
	{
		for (int i = 0; i < NUM_SIDES; i++)
		{
			glVertex2f(verts[i]->x, verts[i]->y);
		}
	}
	glEnd();



	glPopMatrix();
}

void Asteroid::GeneratePoints(Vector2 center, float radius, int numSides, float radianOffset)
{
	const float radiansTotal = 2.0f * MathUtils::pi;
	const float radiansPerSide = radiansTotal / numSides;
	int vertexIndex = 0;

	for (float radians = 0.0f; radians < radiansTotal; radians += radiansPerSide)
	{
		float adjustedRadians = radians + radianOffset;
		float x = center.x + (radius * cos(adjustedRadians) + TheGame::GetRandom(0, ASTEROID_BUMP_MAGNITUDE) - (ASTEROID_BUMP_MAGNITUDE / 2.f));
		float y = center.y + (radius * sin(adjustedRadians) + TheGame::GetRandom(0, ASTEROID_BUMP_MAGNITUDE) - (ASTEROID_BUMP_MAGNITUDE / 2.f));
		verts[vertexIndex++] = new Vector2(x, y);
	}

}

void Asteroid::DrawDebugCircle(Vector2 center, float radius) const
{
	const float radiansTotal = 2.0f * MathUtils::pi;
	const float radiansPerSide = radiansTotal / 40;
	glBegin(GL_LINE_LOOP);
	{
		for (float radians = 0.0f; radians < radiansTotal; radians += radiansPerSide)
		{
			float x = center.x + (radius * cos(radians));
			float y = center.y + (radius * sin(radians));
			glVertex2f(x, y);
		}
	}
	glEnd();
}

void Asteroid::ToggleDebugDraw()
{
	m_debugInfo = !m_debugInfo;
}
