#ifndef _RENDER_MANAGER_H
#define _RENDER_MANAGER_H

#include <vector>
#include <SFML/Graphics/View.hpp>

namespace sf
{
	class Drawable;
}

class WindowManager;

class RenderManager
{
public:

	RenderManager();
	~RenderManager();

	void Initialise(const int& windowWidth, const int& windowHeight, const char* windowTitle);
	void Render();

	void AddRenderObject(sf::Drawable* renderObject);
	void RemoveRenderObject(sf::Drawable* renderObject);

	void AddUIRenderObject(sf::Drawable* renderObject);
	void RemoveUIRenderObject(sf::Drawable* renderObject);
	
	void RemoveGameRenderView();
	/* In an ideal world, I have a view manager (this logic should not be here) */
    sf::View& GetGameRenderView() 
	{
		return m_gameView;
	}

	void PushRenderGroup();
	void PopRenderGroup();

private:

	bool m_Initialised;
	WindowManager* m_pWindowManager;

	sf::View m_gameView;
	sf::View m_UIView;

	std::vector<std::vector<sf::Drawable*>> m_RenderObjects;
	std::vector<std::vector<sf::Drawable*>> m_UIRenderObjects;

};

#endif
