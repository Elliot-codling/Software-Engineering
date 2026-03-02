#include "InputManager.h"
#include "InputDevice.h"

void InputManager::Update()
{
	m_inputDevice->ProcessInputs();
}
