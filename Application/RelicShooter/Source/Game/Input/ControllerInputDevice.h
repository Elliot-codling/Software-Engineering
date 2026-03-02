#pragma once
#include <map>
#include "../../Engine/Input/InputDevice.h"
#include "GamePad.h"

class ControllerInputDevice : public InputDevice
{
public:
    ControllerInputDevice() = default;
    ~ControllerInputDevice() override = default;

    void Initalise();
    void ProcessInputs() override;

private:
    float SlowJoystickAxis(Controller::Analogue axis, GamePad* gamepad);

private:
    const int m_currentJoystickID = 0;       // Controller ID
    const float m_maxDeltaMovement = 4.f;      // Max change for slow thumbstick movment

    // Virtual axis
    std::map<Controller::Analogue, float> m_virtualAxisMap;
};

