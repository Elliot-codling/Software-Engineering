#pragma once
#include "../../Engine/Input/InputDevice.h"
// Easy way to get the inputs from virtual controller

AnalogueInput* GetAnalogueInput(E_AnalogueInput trigger);
DigitalInput* GetDigitalInput(E_DigitalInput button);
InputType GetCurrentInputType();