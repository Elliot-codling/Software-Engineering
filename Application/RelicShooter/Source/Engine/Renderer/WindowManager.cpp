#include "WindowManager.h"

#include <SFML/Graphics.hpp>
#include "../Utils/Utils.h"

WindowManager::~WindowManager()
{
	SAFE_DELETE_PTR(m_pWindow);
}

void WindowManager::InitialiseWindow(const int& windowWidth, const int& windowHeight, const char* windowTitle)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	m_pWindow = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Style::Default, settings);
}
