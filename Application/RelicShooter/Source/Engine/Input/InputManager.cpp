#include "InputManager.h"
#include "InputDevice.h"

InputManager::InputManager()
	:m_pInputDevice(0)
{

}

InputManager::~InputManager()
{

}

void InputManager::Initialise()
{

}

void InputManager::Update()
{
	if (m_pInputDevice)
	{
		m_pInputDevice->ProcessInputs();
	}
}
