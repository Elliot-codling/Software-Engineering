#ifndef _INPUT_DEVICE_H
#define _INPUT_DEVICE_H
#include <chrono>

enum InputType
{
	Keyboard_Mouse,
	Gamepad
};

struct AnalogueInput
{
	AnalogueInput() : m_Value(0.0f) {}
	void SetValue(float value) { m_Value = value; }
	float GetValue() const
	{
		if (m_Value > 1.0f)
		{
			return 1.0f;
		}
		if (m_Value < -1.0f)
		{
			return -1.0f;
		}
		return m_Value;
	}

private:
	float m_Value;
};

enum E_ButtonState
{
	E_ButtonState_Up,
	E_ButtonState_Pressed,
	E_ButtonState_Down
};

struct DigitalInput
{
	DigitalInput() : m_State(E_ButtonState_Up), m_recordedSystemTime(std::chrono::system_clock::now()), m_buttonPressed(false), m_resetButtonPressed(false) {}

	void SetDown(bool pressed)
	{
		// Activate pressed state only once. Next call of function will set to down 
		if (pressed)
		{
			m_State = m_State == E_ButtonState_Up ? E_ButtonState_Pressed : E_ButtonState_Down;
		}
		else
		{
			m_State = E_ButtonState_Up;
		}

		// Record time and set bool
		if (m_State == E_ButtonState_Pressed)
		{
			m_recordedSystemTime = std::chrono::system_clock::now();
			m_buttonPressed = true;
		}
		
		if (m_resetButtonPressed)
		{
			m_resetButtonPressed = false;
			m_buttonPressed = false;
		}

	}
	bool IsPressed() const { return m_State == E_ButtonState_Pressed; }
	bool IsDown() const { return m_State != E_ButtonState_Up; }
	bool IsUp() const { return m_State == E_ButtonState_Up; }
	bool HasCompletedCycle()
	{
		// Check if the cycle has been completed
		if (m_buttonPressed && m_State == E_ButtonState_Up)
		{
			m_resetButtonPressed = true;
			return true;
		}
		
		return false;
	}

	float GetHoldTime() const
	{
		// Returns seconds held			
		std::chrono::duration<float> timeHeld = std::chrono::system_clock::now() - m_recordedSystemTime;
		return timeHeld.count();
	}

private:
	E_ButtonState m_State;
	std::chrono::time_point<std::chrono::system_clock> m_recordedSystemTime;
	bool m_buttonPressed;
	bool m_resetButtonPressed;
}; 

enum E_AnalogueInput
{
	E_AnalogueInput_LeftTrigger,
	E_AnalogueInput_RightTrigger,

	E_AnalogueInput_ThumbLX,
	E_AnalogueInput_ThumbLY,

	E_AnalogueInput_ThumbRX,
	E_AnalogueInput_ThumbRY,

	E_AnalogueInput_MAX
};

enum E_DigitalInput
{
	E_DigitalInput_DpadUp,
	E_DigitalInput_DpadDown,
	E_DigitalInput_DpadLeft,
	E_DigitalInput_DpadRight,

	E_DigitalInput_Start,
	E_DigitalInput_Back,

	E_DigitalInput_LeftThumb,
	E_DigitalInput_RightThumb,

	E_DigitalInput_LeftShoulder,
	E_DigitalInput_RightShoulder,

	E_DigitalInput_A,
	E_DigitalInput_B,
	E_DigitalInput_X,
	E_DigitalInput_Y,

	E_DigitalInput_MAX
};

class InputDevice
{
public:
	InputDevice() {}
	virtual ~InputDevice() {}

	virtual void ProcessInputs() = 0;

	DigitalInput* GetButtonInput(E_DigitalInput button) const
	{
		// Thank you resharper
		return const_cast<DigitalInput*>(&m_DigitalInputs[button]);
	}
	AnalogueInput* GetAnalogueInput(E_AnalogueInput trigger) const
	{
		// I love resharper
		return const_cast<AnalogueInput*>(&m_AnalogueInputs[trigger]);
	}
	InputType GetInputType()
	{
		return m_inputType;
	}


protected:
	AnalogueInput m_AnalogueInputs[E_AnalogueInput_MAX];
	DigitalInput m_DigitalInputs[E_DigitalInput_MAX];

	InputType m_inputType;
};

#endif
