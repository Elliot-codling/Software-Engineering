#include "KeyboardAndMouseInputDevice.h"

#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"

void KeyboardAndMouseInputDevice::Initalise()
{
    const sf::Window& window = C_SysContext::Get<WindowManager>()->GetWindow();
    m_windowWidth = window.getSize().x;
    m_windowHeight = window.getSize().y;

	m_inputType = Keyboard_Mouse;
}

void KeyboardAndMouseInputDevice::ProcessInputs()
{
    /* Character Movement code:
     * Maps WSAD to left thumbstick controls
	 */

    using namespace sf;

    float horizontalSpeed;
    float verticalSpeed;

    // Left stick
    if (HasKeyBeenPressed(Keyboard::W))
    {
        verticalSpeed = -1.f;
    }
    else if (HasKeyBeenPressed(Keyboard::S))
    {
        verticalSpeed = 1.f;
    }
    else
    {
        // Reset movement to 0
        verticalSpeed = 0.f;
    }
    if (HasKeyBeenPressed(Keyboard::A))
    {
        horizontalSpeed = -1.f;
    }
    else if (HasKeyBeenPressed(Keyboard::D))
    {
        horizontalSpeed = 1.f;
    }
    else
    {
        // Reset movement to 0
        horizontalSpeed = 0.f;
    }

	float magnitude = std::sqrt((horizontalSpeed * horizontalSpeed) + (verticalSpeed * verticalSpeed));
    if (magnitude <= 0)
    {
        magnitude = 1.f;
    }

    m_AnalogueInputs[E_AnalogueInput_ThumbLX].SetValue(horizontalSpeed/magnitude);
    m_AnalogueInputs[E_AnalogueInput_ThumbLY].SetValue(verticalSpeed/magnitude);

    // Right stick
    const Window& window = C_SysContext::Get<WindowManager>()->GetWindow();
    Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));

    // Make (0, 0) to the centre of the screen
    const float mouseX = (mousePos.x) - (static_cast<float>(m_windowWidth) / 2.f);
    const float mouseY = (mousePos.y) - (static_cast<float>(m_windowHeight) / 2.f);

    // Calculate percentage moved across the screen
    m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(mouseX / (static_cast<float>(m_windowWidth) / 2.f));
    m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(mouseY / (static_cast<float>(m_windowHeight) / 2.f));

    /* ABXY buttons:
	 * Keyboard controls mapped to gamepad buttons
     */

    // Run
    m_DigitalInputs[E_DigitalInput_A].SetDown(
        HasKeyBeenPressed(Keyboard::LShift) ||
        HasKeyBeenPressed(Keyboard::Space)
    );

    // Drop weapon
    m_DigitalInputs[E_DigitalInput_B].SetDown(
        HasKeyBeenPressed(Keyboard::V) ||
        HasMouseBeenPressed(Mouse::Middle)
        );
    
    // Reload
    m_DigitalInputs[E_DigitalInput_X].SetDown(
        HasKeyBeenPressed(Keyboard::R) ||
		HasKeyBeenPressed(Keyboard::E)
        );
    
    // Switch weapon
    m_DigitalInputs[E_DigitalInput_Y].SetDown(
        HasKeyBeenPressed(Keyboard::Q) ||
        HasKeyBeenPressed(Keyboard::Tab)
        );

    // Scope
    m_AnalogueInputs[E_AnalogueInput_LeftTrigger].SetValue(
        HasMouseBeenPressed(Mouse::Right) ? 1.0f : 0.0f
		);

    // Fire
    m_AnalogueInputs[E_AnalogueInput_RightTrigger].SetValue(
        HasMouseBeenPressed(Mouse::Left) ? 1.0f : 0.0f
		);

    // Throw Grenade
    m_DigitalInputs[E_DigitalInput_LeftShoulder].SetDown(
        HasKeyBeenPressed(Keyboard::F)
		);

    // Recycle weapons for scrap
    m_DigitalInputs[E_DigitalInput_RightShoulder].SetDown(
        HasKeyBeenPressed(Keyboard::X)
		);

    // Pause menu
    m_DigitalInputs[E_DigitalInput_Start].SetDown(
        HasKeyBeenPressed(Keyboard::Escape)
		);
    
}

bool KeyboardAndMouseInputDevice::HasKeyBeenPressed(const sf::Keyboard::Key& key)
{
    return sf::Keyboard::isKeyPressed(key);
}

bool KeyboardAndMouseInputDevice::HasMouseBeenPressed(const sf::Mouse::Button& button)
{
    return sf::Mouse::isButtonPressed(button);
}
