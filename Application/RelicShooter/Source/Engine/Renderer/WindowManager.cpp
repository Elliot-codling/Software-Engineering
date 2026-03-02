#include "WindowManager.h"

#include <SFML/Graphics.hpp>
#include "../Utils/Utils.h"


void WindowManager::InitialiseWindow(const int& windowWidth, const int& windowHeight, const char* windowTitle)
{
	m_window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Style::Close);
}

sf::Color WindowManager::GetWindowColor()
{
	return m_windowColor;
}

void WindowManager::SetWindowColor(sf::Color windowColor)
{
	m_windowColor = windowColor;
}
