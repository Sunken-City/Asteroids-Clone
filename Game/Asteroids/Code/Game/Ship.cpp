#include "Game/Ship.hpp"

#include <math.h>
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Renderer/TheRenderer.hpp"
#include "Game/TheGame.hpp"
#include "Game/TheApp.hpp"
#include "Game/Bullet.hpp"
#include "Engine/Input/XInputController.hpp"

//Changing SHIP_LENGTH will change the entire size of the ship automatically
const float Ship::SHIP_LENGTH = 25.0f;	
const float Ship::SHIP_WIDTH = Ship::SHIP_LENGTH / 2.0f;
const float Ship::SHIP_BAR_X = Ship::SHIP_WIDTH - Ship::SHIP_LENGTH * 0.08f;
const float Ship::SHIP_BAR_Y = Ship::SHIP_LENGTH * 0.7f;
const float Ship::THRUST_X = Ship::SHIP_WIDTH * 0.7f;
const float Ship::THRUST_Y = Ship::SHIP_LENGTH * 0.5f;
const float Ship::THRUST_VARIANCE = Ship::SHIP_LENGTH * 0.25f;
const float Ship::SHIP_DEATH_ANIM_SECONDS = 2.0f;

Ship::Ship(XInputController* controller) : m_controller(controller)
{
	Spawn();
	InitializeVerts();
}

Ship::~Ship()
{
	for (int i = 0; i < NUM_SHIP_VERTS; i++)
	{
		delete m_shipVerts[i];
	}
	for (int i = 0; i < NUM_THRUST_VERTS; i++)
	{
		delete m_thrustVerts[i];
	}
}

void Ship::Update(float deltaSeconds)
{
	if (m_controller->JustPressed(XboxButton::START))
	{
		Spawn();
	}
	if (m_isDead)
	{
		m_acceleration = Vector2(0.0f, 0.0f);
		Entity::Update(deltaSeconds);
		return;
	}
	
	Thrust();

	if (m_controller->JustPressed(XboxButton::A))
	{
		FireWeapon();
	}

	Vector2 leftStickDirection = m_controller->GetLeftStickPosition();

	//If we're out of the inner deadzone, change our ship's angle.
	if (leftStickDirection.CalculateMagnitude() > 0.153f)
	{
		m_orientation = MathUtils::RadiansToDegrees(atan2(leftStickDirection.y, leftStickDirection.x));
	}

	if (m_controller->GetControllerNumber() == 0)
	{
		const float TURN_DEGREES_PER_SECOND = 200.f;
		float turnDegreesThisFrame = TURN_DEGREES_PER_SECOND * deltaSeconds;
		UpdateFromKeyboardControls(turnDegreesThisFrame);
	}

	m_thrustColor = MathUtils::RangeMap(sin(m_ageInSeconds * 10.0f), -1.0f, 1.0f, 0.0f, 1.0f);

	Entity::Update(deltaSeconds);
}

void Ship::Render() const
{
	TheRenderer::instance->PushMatrix();

	Entity::Render();

	TheRenderer::instance->Translate(m_position.x, m_position.y, 0.0f);
	TheRenderer::instance->Rotate(m_orientation - 90.0f, 0.0f, 0.0f, 1.0f);

	if (!m_isDead)
	{
		TheRenderer::instance->SetColor(1.0f, m_thrustColor, 0.0f, 1.0f);
		TheRenderer::instance->DrawLines(m_thrustVerts, NUM_THRUST_VERTS, 2.f);
	}

	float red = m_controller->GetControllerNumber() == 1 ? 0.0f : 1.0f;
	float green = m_controller->GetControllerNumber() == 3 ? 0.0f : 1.0f;
	float blue = m_controller->GetControllerNumber() == 2 ? 0.0f : 1.0f;

	TheRenderer::instance->SetColor(red, green, blue, 1.0f);

	if (m_isDead)
	{
		RenderAsDead(red, green, blue);
	}

	TheRenderer::instance->DrawLines(m_shipVerts, NUM_SHIP_VERTS, 2.f);

	TheRenderer::instance->PopMatrix();
}

void Ship::InitializeVerts()
{
	m_shipVerts[0] = new Vector2(0.0f, SHIP_LENGTH);
	m_shipVerts[1] = new Vector2(SHIP_WIDTH, -SHIP_LENGTH);

	m_shipVerts[2] = new Vector2(0.0f, SHIP_LENGTH);
	m_shipVerts[3] = new Vector2(-SHIP_WIDTH, -SHIP_LENGTH);

	m_shipVerts[4] = new Vector2(-SHIP_BAR_X, -SHIP_BAR_Y);
	m_shipVerts[5] = new Vector2(SHIP_BAR_X, -SHIP_BAR_Y);

	//Initialize the thruster verts as well. These are separate so we can give them a different color.
	m_thrustVerts[0] = new Vector2(-THRUST_X, -SHIP_BAR_Y);
	m_thrustVerts[LEFT_THRUST_INDEX] = new Vector2(THRUST_X, -SHIP_BAR_Y);

	m_thrustVerts[RIGHT_THRUST_INDEX] = new Vector2(-THRUST_X, -SHIP_BAR_Y);
	m_thrustVerts[3] = new Vector2(THRUST_X, -SHIP_BAR_Y);
}

void Ship::Crash()
{
	m_isDead = true;
	m_ageAtDeath = m_ageInSeconds;
	m_controller->VibrateForSeconds(0.5f, XInputController::LARGE_VIBRATE, XInputController::LARGE_VIBRATE);
}

void Ship::Spawn()
{
	if (m_isDead)
	{
		m_position = Vector2(800.0f, 450.0f);
		m_velocity = Vector2(0.0f, 0.0f);
		m_acceleration = Vector2(0.0f, 0.0f);

		m_angularVelocity = 0.0f;
		m_orientation = 90.0f;

		m_cosmeticRadius = SHIP_LENGTH;
		m_physicalRadius = SHIP_LENGTH / 1.5f;

		m_isDead = false;
	}
}

void Ship::UpdateFromKeyboardControls(float turnDegreesThisFrame)
{
	if (TheApp::instance->WasKeyJustPressed('P'))
	{
		Spawn();
	}
	if (TheApp::instance->WasKeyJustPressed(' '))
	{
		TheGame::instance->SpawnBullet(GetNosePosition(), m_velocity, m_orientation, m_controller->GetControllerNumber(), 500, 2.0f);
	}
	if (TheApp::instance->IsKeyDown('A'))
	{
		m_orientation += turnDegreesThisFrame;
	}
	else if (TheApp::instance->IsKeyDown('D'))
	{
		m_orientation -= turnDegreesThisFrame;
	}
}

Vector2 Ship::GetNosePosition() const
{
	return m_position + (Vector2(cos(MathUtils::DegreesToRadians(m_orientation)), sin(MathUtils::DegreesToRadians(m_orientation))) * static_cast<float>(SHIP_LENGTH));
}

void Ship::Thrust()
{
	const float THRUST_PER_SECOND = 200.f;
	float thrustStrength = ((float)m_controller->GetRightTrigger() / 255.0f);
	m_controller->Vibrate(0, XInputController::MEDIUM_VIBRATE * static_cast<int>(thrustStrength));

	if (TheApp::instance->IsKeyDown('W'))
	{
		thrustStrength = 1.0f;
	}

	if (m_controller->GetRightTrigger() > 0 || (TheApp::instance->IsKeyDown('W') && m_controller->GetControllerNumber() == 0))
	{
		float thrustSpeed = THRUST_PER_SECOND * thrustStrength;
		float adjustedThrustLength = thrustStrength * THRUST_Y;
		float thrustAmount = static_cast<float>(TheGame::GetRandom(static_cast<int>(adjustedThrustLength), static_cast<int>((adjustedThrustLength)+THRUST_VARIANCE)));
		float thrustDistance = SHIP_BAR_Y + thrustAmount;

		m_acceleration = Vector2(thrustSpeed * cos(MathUtils::DegreesToRadians(m_orientation)), thrustSpeed * sin(MathUtils::DegreesToRadians(m_orientation)));
		//Set the cosmetic radius to encompass the new animation. This will prevent popping when screen wrapping.
		m_cosmeticRadius = SHIP_LENGTH + thrustDistance - SHIP_BAR_Y;
		m_thrustVerts[LEFT_THRUST_INDEX]->SetXY(0.0f, -thrustDistance);
		m_thrustVerts[RIGHT_THRUST_INDEX]->SetXY(0.0f, -thrustDistance);
	}
	else
	{
		m_acceleration = Vector2(0.0f, 0.0f);
		m_cosmeticRadius = SHIP_LENGTH;
		m_thrustVerts[LEFT_THRUST_INDEX]->SetXY(THRUST_X, -SHIP_BAR_Y);
		m_thrustVerts[RIGHT_THRUST_INDEX]->SetXY(-THRUST_X, -SHIP_BAR_Y);
		m_thrustColor = 0.0f;
	}

}

void Ship::FireWeapon()
{
	//Standard "pistol" gun. Fires a single shot straight ahead. Well-rounded
	if (m_controller->GetControllerNumber() == 0)
	{
		TheGame::instance->SpawnBullet(GetNosePosition(), m_velocity, m_orientation, m_controller->GetControllerNumber(), 500, 2.0f);
	}
	//Shotgun. Fires an inaccurate burst that does lots of damage, but has extremely limited range.
	if (m_controller->GetControllerNumber() == 1)
	{
		TheGame::instance->SpawnBullet(GetNosePosition(), m_velocity, m_orientation + static_cast<float>(TheGame::instance->GetRandom(0, 60) - 30), m_controller->GetControllerNumber(), 500, 0.3f);
		TheGame::instance->SpawnBullet(GetNosePosition(), m_velocity, m_orientation + static_cast<float>(TheGame::instance->GetRandom(0, 60) - 30), m_controller->GetControllerNumber(), 500, 0.3f);
		TheGame::instance->SpawnBullet(GetNosePosition(), m_velocity, m_orientation + static_cast<float>(TheGame::instance->GetRandom(0, 60) - 30), m_controller->GetControllerNumber(), 500, 0.3f);
	}
	//V gun. Shoots two bullets 45 degrees off-center, giving this player a more interesting strategy
	if (m_controller->GetControllerNumber() == 2)
	{
		TheGame::instance->SpawnBullet(GetNosePosition(), m_velocity, m_orientation + 45.0f, m_controller->GetControllerNumber(), 400, 1.5f);
		TheGame::instance->SpawnBullet(GetNosePosition(), m_velocity, m_orientation - 45.0f, m_controller->GetControllerNumber(), 400, 1.5f);
	}
	//Velocity-dependent gun. The faster you go, the faster your bullets go. Encourages high-risk, high-reward play.
	if (m_controller->GetControllerNumber() == 3)
	{
		TheGame::instance->SpawnBullet(GetNosePosition(), m_velocity, m_orientation, m_controller->GetControllerNumber(), m_velocity.CalculateMagnitude() + 100.f, 2.0f);
	}
}


void Ship::RenderAsDead(float red, float green, float blue) const
{
	const float secondsSinceDeath = m_ageInSeconds - m_ageAtDeath;
	float fractionComplete = secondsSinceDeath / SHIP_DEATH_ANIM_SECONDS;

	TheRenderer::instance->PushMatrix();
	TheRenderer::instance->SetColor(1.f, (float)TheGame::GetRandom(0, 255) / 255.f, 0.f, MathUtils::Clamp(1.f - fractionComplete, 0.f, 1.f));
	TheRenderer::instance->DrawPolygon(Vector2(0.f, 0.f), static_cast<float>(TheGame::GetRandom(10, static_cast<int>(m_cosmeticRadius))), 30, 0);
	TheRenderer::instance->PopMatrix();

	TheRenderer::instance->SetColor(red, green, blue, MathUtils::Clamp(1.f - fractionComplete, 0.f, 1.f));
	TheRenderer::instance->Scale(MathUtils::Clamp(1.f - fractionComplete, 0.f, 1.f), MathUtils::Clamp(1.f - fractionComplete, 0.f, 1.f), 1.0f);
}
