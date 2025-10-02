#ifndef _WINDOW_MANAGER_H
#define _WINDOW_MANAGER_H

namespace sf
{
	class RenderWindow;
}

class WindowManager
{
public:
	WindowManager() : m_pWindow(nullptr) {}
	~WindowManager();

	void InitialiseWindow(const int& windowWidth, const int& windowHeight, const char* windowTitle);
	sf::RenderWindow* GetWindow() { return m_pWindow; }

private:

	sf::RenderWindow* m_pWindow;

};

#endif
