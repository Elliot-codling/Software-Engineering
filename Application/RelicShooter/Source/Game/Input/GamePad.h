#pragma once
#include <windows.h>
#include <Xinput.h>
//Dpad support to be added later

namespace Controller
{
	
	enum Analogue
	{
		ThumbLX,
		ThumbLY,
		ThumbRX,
		ThumbRY,
		LeftTrigger,
		RightTrigger
	};

	enum Buttons
	{
		GamePadA = XINPUT_GAMEPAD_A,
		GamePadB = XINPUT_GAMEPAD_B,
		GamePadX = XINPUT_GAMEPAD_X,
		GamePadY = XINPUT_GAMEPAD_Y,

		GamePadLB = XINPUT_GAMEPAD_LEFT_SHOULDER,
		GamePadRB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		GamePadBack = XINPUT_GAMEPAD_BACK,
		GamePadStart = XINPUT_GAMEPAD_START,
		GamePadLT = XINPUT_GAMEPAD_LEFT_THUMB,
		GamePadRT = XINPUT_GAMEPAD_RIGHT_THUMB,
	};
	
}


class GamePad
{
public:
	GamePad() = default;
	~GamePad() = default;

public:
	bool CheckConnection();
	float GetJoystickAxis(Controller::Analogue axis);
	bool GetJoystickButton(Controller::Buttons button);

private:

	float ClampValue(float value, float lower, float upper);
	SHORT GetAnalogueInput(Controller::Analogue axis);

private:
	XINPUT_STATE m_state;
	int m_controllerID;

	const float m_thumbstickMinDeadzone = 0.1f;
	const float m_thumbstickMaxDeadzone = 0.9f;

};

