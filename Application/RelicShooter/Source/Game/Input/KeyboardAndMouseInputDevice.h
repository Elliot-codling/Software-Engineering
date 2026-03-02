#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "../../Engine/Input/InputDevice.h"

class KeyboardAndMouseInputDevice : public InputDevice
{
public:
    KeyboardAndMouseInputDevice() = default;
    ~KeyboardAndMouseInputDevice() = default;

    void Initalise();
    void ProcessInputs();

private:
    bool HasKeyBeenPressed(const sf::Keyboard::Key& key);
    bool HasMouseBeenPressed(const sf::Mouse::Button& button);

private:
    size_t m_windowWidth;
    size_t m_windowHeight;
};
