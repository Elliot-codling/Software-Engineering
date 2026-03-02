#include "RenderManager.h"
#include "../Utils/Utils.h"
#include "../System/Context/SysContextProvider.h"
#include "WindowManager.h"
#include <SFML/Graphics.hpp>

#include "../../Game/DebugHandler.hpp"

RenderManager::RenderManager()
	:m_Initialised(false)
	,m_pWindowManager(nullptr)
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::Initialise(const int& windowWidth, const int& windowHeight, const char* windowTitle)
{
	if (m_Initialised)
		return;

	m_pWindowManager = C_SysContext::Get<WindowManager>();
	m_pWindowManager->InitialiseWindow(windowWidth, windowHeight, windowTitle);

	m_gameView = m_pWindowManager->GetWindow().getDefaultView();
	m_UIView = m_pWindowManager->GetWindow().getDefaultView();

	m_Initialised = true;
}

void RenderManager::Render()
{
	if (!m_Initialised)
		return;

	if (m_pWindowManager->GetWindow().isOpen())
	{
		sf::Event event;
		while (m_pWindowManager->GetWindow().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_pWindowManager->GetWindow().close();
				return;
			}
		}
		m_pWindowManager->GetWindow().clear(m_pWindowManager->GetWindowColor());

		/* Game View */
		m_pWindowManager->GetWindow().setView(m_gameView);

		if( m_RenderObjects.size() > 0 )
		{
			std::vector<std::vector<sf::Drawable*>>::reverse_iterator stateIter = m_RenderObjects.rbegin();

			std::vector<sf::Drawable*>::iterator iter;
			for (iter = (*stateIter).begin(); iter != (*stateIter).end(); iter++)
			{
				m_pWindowManager->GetWindow().draw(*(*iter));
			}
		}

		/* UI View */
		m_pWindowManager->GetWindow().setView(m_UIView);

		if (m_UIRenderObjects.size() > 0)
		{
		    std::vector<std::vector<sf::Drawable*>>::reverse_iterator stateUIIter = m_UIRenderObjects.rbegin();

			std::vector<sf::Drawable*>::iterator iter;
			for (iter = (*stateUIIter).begin(); iter != (*stateUIIter).end(); iter++) {
				m_pWindowManager->GetWindow().draw(*(*iter));
			}
		}

		m_pWindowManager->GetWindow().display();
	}
}

void RenderManager::AddRenderObject(sf::Drawable* renderObject)
{
	m_RenderObjects.back().emplace_back(renderObject);
}

void RenderManager::RemoveRenderObject(sf::Drawable* renderObject)
{
	if (m_RenderObjects.empty())
	{
		// If the render has already been destroyed, then dont bother deleting anything
		return;
	}

	std::vector<sf::Drawable*>::iterator iter;
	for (iter = m_RenderObjects.back().begin(); iter != m_RenderObjects.back().end(); )
	{
		if (*iter == renderObject)
		{
			iter = m_RenderObjects.back().erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void RenderManager::AddUIRenderObject(sf::Drawable* renderObject) {
	m_UIRenderObjects.back().push_back(renderObject);
}

void RenderManager::RemoveUIRenderObject(sf::Drawable* renderObject) {
	if (m_UIRenderObjects.empty())
	{
		// If the render has already been destroyed, then dont bother deleting anything
		return;
	}

	std::vector<sf::Drawable*>::iterator iter;
	for (iter = m_UIRenderObjects.back().begin(); iter != m_UIRenderObjects.back().end(); )
	{
		if (*iter == renderObject)
		{
			iter = m_UIRenderObjects.back().erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void RenderManager::RemoveGameRenderView() {
	m_gameView = m_pWindowManager->GetWindow().getDefaultView();
}


void RenderManager::PushRenderGroup()
{
	m_RenderObjects.emplace_back(std::vector<sf::Drawable*>());
	m_UIRenderObjects.emplace_back(std::vector<sf::Drawable*>());
}

void RenderManager::PopRenderGroup()
{
	m_RenderObjects.pop_back();
	m_UIRenderObjects.pop_back();
}
