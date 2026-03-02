#include "GamePad.h"
#include <cmath>

bool GamePad::CheckConnection()
{
	ZeroMemory(&m_state, sizeof(XINPUT_STATE));
	if (XInputGetState(m_controllerID, &m_state) == ERROR_SUCCESS)
	{
		return true;
	}
	return false;
	
}

float GamePad::GetJoystickAxis(Controller::Analogue axis)
{
	if (!CheckConnection())
	{
		return 0.f;
	}

	float normalisedValue;
	switch (axis)
	{
	case Controller::LeftTrigger:
	case Controller::RightTrigger:
		normalisedValue = static_cast<float>(GetAnalogueInput(axis)) / 255;
		break;
	default:
		normalisedValue = static_cast<float>(GetAnalogueInput(axis)) / 32767.f;
	}
	
	normalisedValue = ClampValue(normalisedValue, -1.f, 1.f);

	if (std::abs(normalisedValue) < m_thumbstickMinDeadzone)
	{
		return 0.f;
	}
	if (std::abs(normalisedValue) > m_thumbstickMaxDeadzone)
	{
		return normalisedValue > 0 ? 1.f : -1.f;
	}

	return normalisedValue;
}

bool GamePad::GetJoystickButton(Controller::Buttons button)
{
	if (!CheckConnection())
	{
		return false;
	}
	return (m_state.Gamepad.wButtons & button) != 0;
}

float GamePad::ClampValue(float value, float lower, float upper)
{
	if (value > upper)
	{
		return upper;
	}
	if (value < lower)
	{
		return lower;
	}
	return value;
}

SHORT GamePad::GetAnalogueInput(Controller::Analogue axis)
{
	// Convert enum type to XInput analogue input
	switch (axis)
	{
	case Controller::ThumbLX:
		return m_state.Gamepad.sThumbLX;
	case Controller::ThumbLY:
		return m_state.Gamepad.sThumbLY;
	case Controller::ThumbRX:
		return m_state.Gamepad.sThumbRX;
	case Controller::ThumbRY:
		return m_state.Gamepad.sThumbRY;
	case Controller::LeftTrigger:
		return m_state.Gamepad.bLeftTrigger;
	case Controller::RightTrigger:
		return m_state.Gamepad.bRightTrigger;
	}
}
