#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

class InputDevice;

class InputManager
{
public:
	InputManager();
	~InputManager();

	static void Initialise();
	void Update();

	InputDevice* GetInputDevice() const { return m_pInputDevice; }
	void SetInputDevice(InputDevice* pInputDevice) { m_pInputDevice = pInputDevice; }

private:

	InputDevice* m_pInputDevice;
};

#endif
