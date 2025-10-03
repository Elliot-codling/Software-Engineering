#include "RenderManager.h"
#include "../Utils/Utils.h"
#include "../System/Context/SysContextProvider.h"
#include "WindowManager.h"
#include <SFML/Graphics.hpp>

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

	m_Initialised = true;
}

void RenderManager::Render()
{
	if (!m_Initialised)
		return;

	if (m_pWindowManager->GetWindow()->isOpen())
	{
		sf::Event event;
		while (m_pWindowManager->GetWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_pWindowManager->GetWindow()->close();
				return;
			}
		}

		m_pWindowManager->GetWindow()->clear();

		if( m_RenderObjects.size() > 0 )
		{
			std::vector<std::vector<sf::Drawable*>>::reverse_iterator stateIter = m_RenderObjects.rbegin();

			std::vector<sf::Drawable*>::iterator iter;
			for (iter = (*stateIter).begin(); iter != (*stateIter).end(); iter++)
			{
				m_pWindowManager->GetWindow()->draw(*(*iter));
			}
		}
			
		m_pWindowManager->GetWindow()->display();
		
	}
}

void RenderManager::AddRenderObject(sf::Drawable* renderObject)
{
	m_RenderObjects.back().push_back(renderObject);
}

void RenderManager::RemoveRenderObject(sf::Drawable* renderObject)
{
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

void RenderManager::PushRenderGroup()
{
	m_RenderObjects.push_back(std::vector<sf::Drawable*>());
}

void RenderManager::PopRenderGroup()
{
	m_RenderObjects.pop_back();
}
