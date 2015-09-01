#pragma once

const int NUM_KEYS = 256;

class TheApp
{
public:
	TheApp();
	TheApp(float width, float height);
	void SetKeyDownStatus(unsigned char keyCode, bool isDown);
	bool isKeyDown(unsigned char keyCode);

	void SetWindowWidth(float width);
	void SetWindowHeight(float height);
	float GetWindowWidth();
	float GetWindowHeight();

	static TheApp* instance;

private:
	bool m_isKeyDown[NUM_KEYS];
	float m_frameCounter = 0.0f;
	float m_windowWidth;
	float m_windowHeight;
};
