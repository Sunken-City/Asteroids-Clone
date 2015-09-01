#include "Game/TheApp.hpp"

TheApp* TheApp::instance = nullptr;

bool TheApp::isKeyDown(unsigned char keyCode)
{
	return m_isKeyDown[keyCode];
}

void TheApp::SetWindowWidth(float width)
{
	m_windowWidth = width;
}

void TheApp::SetWindowHeight(float height)
{
	m_windowHeight = height;
}

float TheApp::GetWindowWidth()
{
	return m_windowWidth;
}

float TheApp::GetWindowHeight()
{
	return m_windowHeight;
}

TheApp::TheApp()
{
	//Initialize all keys to up
	for (int keyIndex = 0; keyIndex < NUM_KEYS; ++keyIndex)
	{
		m_isKeyDown[keyIndex] = false;
	}
}

TheApp::TheApp(float width, float height) : m_windowWidth(width), m_windowHeight(height)
{
	//Initialize all keys to up
	for (int keyIndex = 0; keyIndex < NUM_KEYS; ++keyIndex)
	{
		m_isKeyDown[keyIndex] = false;
	}
}

void TheApp::SetKeyDownStatus(unsigned char keyCode, bool isNowDown)
{
	m_isKeyDown[keyCode] = isNowDown;
}
