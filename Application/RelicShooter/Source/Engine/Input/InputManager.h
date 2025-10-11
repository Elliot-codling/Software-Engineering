#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

class InputDevice;

class InputManager
{
public:
	InputManager();
	~InputManager();

	void Initialise();
	void Update();

	InputDevice* GetInputDevice() { return m_pInputDevice; };
	void SetInputDevice(InputDevice* pInputDevice) { m_pInputDevice = pInputDevice; }

private:

	InputDevice* m_pInputDevice;
};

#endif
