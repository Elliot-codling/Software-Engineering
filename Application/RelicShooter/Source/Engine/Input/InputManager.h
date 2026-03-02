#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H
#include <memory>

#include "InputDevice.h"

class InputManager
{
public:
	InputManager() = default;
	~InputManager() = default;

	void Update();

	InputDevice* GetInputDevice() { return m_inputDevice.get(); }
	void SetInputDevice(std::unique_ptr<InputDevice> inputDevice)
	{
		m_inputDevice = std::move(inputDevice);
	}

private:
	std::unique_ptr<InputDevice> m_inputDevice;
};

#endif
