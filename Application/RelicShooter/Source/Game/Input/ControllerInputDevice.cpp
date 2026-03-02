#include "ControllerInputDevice.h"

#include <cmath>
#include "GamePadManager.h"
#include "../../Engine/Renderer/FrameTimer.h"
#include "../../Engine/System/Context/SysContextProvider.h"

// X and Y are on the left stick
// PovX and PovY are the D-Pad
// U is right stick horizontal
// V is right stick vertical
// Z is the triggers, negative is right, positive is left

void ControllerInputDevice::Initalise()
{
    m_inputType = Gamepad;
}

void ControllerInputDevice::ProcessInputs()
{
    /* Character Movement code:
     * Maps WSAD to left thumbstick controls
     */

    GamePad* gamepad = GamePadManager::Get().GetGamePad(m_currentJoystickID);

	// Left stick
    float horizontalSpeed = gamepad->GetJoystickAxis(Controller::ThumbLX);
    float verticalSpeed = -gamepad->GetJoystickAxis(Controller::ThumbLY);

    float magnitude = std::sqrt((horizontalSpeed * horizontalSpeed) + (verticalSpeed * verticalSpeed));
    if (magnitude <= 0)
    {
        magnitude = 1.f;
    }

    m_AnalogueInputs[E_AnalogueInput_ThumbLX].SetValue(horizontalSpeed/magnitude);
	m_AnalogueInputs[E_AnalogueInput_ThumbLY].SetValue(verticalSpeed/magnitude);

    // Right stick
    m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(SlowJoystickAxis(Controller::ThumbRX, gamepad));
    m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(-SlowJoystickAxis(Controller::ThumbRY, gamepad));

	// Run
    m_DigitalInputs[E_DigitalInput_A].SetDown(
        gamepad->GetJoystickButton(Controller::GamePadA) ||
        gamepad->GetJoystickButton(Controller::GamePadLT)
    );

    // Melee
    m_DigitalInputs[E_DigitalInput_B].SetDown(gamepad->GetJoystickButton(Controller::GamePadB));

    // Reload or Use
    m_DigitalInputs[E_DigitalInput_X].SetDown(gamepad->GetJoystickButton(Controller::GamePadX));

    // Switch weapon
    m_DigitalInputs[E_DigitalInput_Y].SetDown(gamepad->GetJoystickButton(Controller::GamePadY));

    // Scope
    m_AnalogueInputs[E_AnalogueInput_LeftTrigger].SetValue(gamepad->GetJoystickAxis(Controller::LeftTrigger));

    // Fire
    m_AnalogueInputs[E_AnalogueInput_RightTrigger].SetValue(gamepad->GetJoystickAxis(Controller::RightTrigger));
    
	// Throw Grenade
    m_DigitalInputs[E_DigitalInput_LeftShoulder].SetDown(gamepad->GetJoystickButton(Controller::GamePadLB));

    // Recycle weapons for scrap
    m_DigitalInputs[E_DigitalInput_RightShoulder].SetDown(gamepad->GetJoystickButton(Controller::GamePadRB));

    // Pause menu
    m_DigitalInputs[E_DigitalInput_Start].SetDown(gamepad->GetJoystickButton(Controller::GamePadStart));
	
}

float ControllerInputDevice::SlowJoystickAxis(Controller::Analogue axis, GamePad* gamepad)
{
	const float value = gamepad->GetJoystickAxis(axis);

	// Get the mapped value, this will create the entry if it doesn't exist
    float& mapValue = m_virtualAxisMap[axis];
    const float maxMovementSpeed = m_maxDeltaMovement * C_SysContext::Get<FrameTimer>()->DeltaTime();
    if (value > mapValue + maxMovementSpeed)
    {
        mapValue += maxMovementSpeed;
    }
    else if (value < mapValue - maxMovementSpeed)
    {
        mapValue -= maxMovementSpeed;
    }
    else
    {
        mapValue = value;
	}

    return mapValue;

}
