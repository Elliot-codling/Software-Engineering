#ifndef _WINDOW_MANAGER_H
#define _WINDOW_MANAGER_H
#include <SFML/Graphics/RenderWindow.hpp>


class WindowManager
{
public:
	WindowManager() = default;
	~WindowManager() =  default;

	void InitialiseWindow(const int& windowWidth, const int& windowHeight, const char* windowTitle);
	sf::RenderWindow& GetWindow() { return m_window; }

	// --- Window colour ---
	sf::Color GetWindowColor();
	void SetWindowColor(sf::Color windowColor);

private:

	sf::Color m_windowColor = {0, 0, 0};
	sf::RenderWindow m_window;

};

#endif
