#include "InputWrapper.h"

#include "../../Engine/Input/InputManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"

AnalogueInput* GetAnalogueInput(E_AnalogueInput trigger)
{
    InputManager* inputManager = C_SysContext::Get<InputManager>();
    InputDevice* inputDevice = inputManager->GetInputDevice();

    return inputDevice->GetAnalogueInput(trigger);
}

DigitalInput* GetDigitalInput(E_DigitalInput button)
{
    InputManager* inputManager = C_SysContext::Get<InputManager>();
    InputDevice* inputDevice = inputManager->GetInputDevice();

    return inputDevice->GetButtonInput(button);
}

InputType GetCurrentInputType()
{
    InputManager* inputManager = C_SysContext::Get<InputManager>();
    InputDevice* inputDevice = inputManager->GetInputDevice();

    return inputDevice->GetInputType();
}
