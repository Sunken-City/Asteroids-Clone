#include "Game/Ship.hpp"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl/gl.h>
#include <math.h>

#include "Engine/Math/MathUtils.hpp"
#include "Game/TheGame.hpp"
#include "Game/TheApp.hpp"

//Changing SHIP_LENGTH will change the entire size of the ship automatically
const float Ship::SHIP_LENGTH = 25.0f;	
const float Ship::SHIP_WIDTH = Ship::SHIP_LENGTH / 2.0f;
const float Ship::SHIP_BAR_X = Ship::SHIP_WIDTH - Ship::SHIP_LENGTH * 0.08f;
const float Ship::SHIP_BAR_Y = Ship::SHIP_LENGTH * 0.7f;
const float Ship::THRUST_X = Ship::SHIP_WIDTH * 0.7f;
const float Ship::THRUST_Y = Ship::SHIP_LENGTH * 0.5f;
const float Ship::THRUST_VARIANCE = Ship::SHIP_LENGTH * 0.25f;

bool Ship::m_debugInfo = false;

Ship::Ship() : m_isAlive(false)
{
	Spawn();
	InitializeVerts();
}

Ship::~Ship()
{
	for (int i = 0; i < NUM_VERTS; i++)
	{
		delete verts[i];
	}
}

void Ship::Update(float deltaSeconds)
{
	const float TURN_DEGREES_PER_SECOND = 200.f;
	const float THRUST_PER_SECOND = 200.f;
	float turnDegreesThisFrame = TURN_DEGREES_PER_SECOND * deltaSeconds;

	if (m_isAlive)
	{
		if (TheApp::instance->isKeyDown('W'))
		{
			m_acceleration = Vector2( THRUST_PER_SECOND * cos(MathUtils::DegreesToRadians( m_orientation)), THRUST_PER_SECOND * sin(MathUtils::DegreesToRadians(m_orientation)));

			float thrustDistance = SHIP_BAR_Y + TheGame::GetRandom(static_cast<int>(THRUST_Y), static_cast<int>(THRUST_Y + THRUST_VARIANCE));
			//Set the cosmetic radius to encompass the new animation. This will prevent popping when screen wrapping.
			m_cosmeticRadius = SHIP_LENGTH + thrustDistance - SHIP_BAR_Y;
			verts[LEFT_THRUST_INDEX]->SetXY(0.0f, -thrustDistance);
			verts[RIGHT_THRUST_INDEX]->SetXY(0.0f, -thrustDistance);
		}
		else
		{
			m_acceleration = Vector2(0.0f, 0.0f);


			m_cosmeticRadius = SHIP_LENGTH;
			verts[LEFT_THRUST_INDEX]->SetXY(THRUST_X, -SHIP_BAR_Y);
			verts[RIGHT_THRUST_INDEX]->SetXY(-THRUST_X, -SHIP_BAR_Y);
		}

		if (TheApp::instance->isKeyDown('A'))
		{
			m_orientation += turnDegreesThisFrame;
		}
		else if (TheApp::instance->isKeyDown('D'))
		{
			m_orientation -= turnDegreesThisFrame;
		}

		Entity::Update(deltaSeconds);
	}
}

void Ship::Render() const
{
	if (m_isAlive)
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
		glRotatef(m_orientation - 90.0f, 0.0f, 0.0f, 1.0f);

		glBegin(GL_LINES);
		{
			for (int i = 0; i < NUM_VERTS; i++)
			{
				glVertex2f(verts[i]->x, verts[i]->y);
			}
		}
		glEnd();
		glPopMatrix();
	}
}

void Ship::InitializeVerts()
{
	verts[0] = new Vector2(0.0f, SHIP_LENGTH);
	verts[1] = new Vector2(SHIP_WIDTH, -SHIP_LENGTH);

	verts[2] = new Vector2(0.0f, SHIP_LENGTH);
	verts[3] = new Vector2(-SHIP_WIDTH, -SHIP_LENGTH);

	verts[4] = new Vector2(-SHIP_BAR_X, -SHIP_BAR_Y);
	verts[5] = new Vector2(SHIP_BAR_X, -SHIP_BAR_Y);

	verts[6] = new Vector2(-THRUST_X, -SHIP_BAR_Y);

	verts[LEFT_THRUST_INDEX] = new Vector2(THRUST_X, -SHIP_BAR_Y);
	verts[RIGHT_THRUST_INDEX] = new Vector2(-THRUST_X, -SHIP_BAR_Y);

	verts[9] = new Vector2(THRUST_X, -SHIP_BAR_Y);
}

void Ship::DrawDebugCircle(Vector2 center, float radius) const
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

void Ship::Crash()
{
	m_isAlive = false;
}

void Ship::Spawn()
{
	if (!m_isAlive)
	{
		m_position = Vector2(800.0f, 450.0f);
		m_velocity = Vector2(0.0f, 0.0f);
		m_acceleration = Vector2(0.0f, 0.0f);

		m_angularVelocity = 0.0f;
		m_orientation = 90.0f;

		m_cosmeticRadius = SHIP_LENGTH;
		m_physicalRadius = SHIP_LENGTH / 1.5f;

		m_isAlive = true;
	}
}

bool Ship::IsAlive()
{
	return m_isAlive;
}

void Ship::ToggleDebugDraw()
{
	m_debugInfo = !m_debugInfo;
}
