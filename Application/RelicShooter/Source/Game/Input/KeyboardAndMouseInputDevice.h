#pragma once
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/Renderer/WindowManager.h"

class KeyboardAndMouseInputDevice : public InputDevice
{
public:
    KeyboardAndMouseInputDevice() = default;
    ~KeyboardAndMouseInputDevice() override = default;

    void ProcessInputs() override;
};
