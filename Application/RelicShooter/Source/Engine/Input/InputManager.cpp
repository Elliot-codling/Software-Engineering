#include "InputManager.h"
#include "InputDevice.h"

InputManager::InputManager()
	:m_pInputDevice(nullptr)
{

}

InputManager::~InputManager()
= default;

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
