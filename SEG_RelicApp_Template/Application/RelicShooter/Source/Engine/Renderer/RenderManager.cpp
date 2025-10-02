#include "RenderManager.h"
#include "../System/Context/SysContextProvider.h"
#include "WindowManager.h"
#include <SFML/Graphics.hpp>

RenderManager::RenderManager()
	:m_Initialised(false)
	,m_pWindowManager(nullptr)
{
}

RenderManager::~RenderManager()
= default;

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



	/*
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	*/
	if (m_pWindowManager->GetWindow()->isOpen())
	{
		sf::Event event{};
		while (m_pWindowManager->GetWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_pWindowManager->GetWindow()->close();
				return;
			}
		}

		auto* twndw = m_pWindowManager->GetWindow();
		twndw->clear();

		if(m_RenderObjects.empty())
			return;

		//Only Draw the Top Most Game State
		{
			const auto stateIter = m_RenderObjects.rbegin();
			for (const auto* tdraw : *stateIter)
			{
				if(tdraw)
					twndw->draw(*tdraw);
			}
		}			
		m_pWindowManager->GetWindow()->display();
		
	}
}

void RenderManager::AddRenderObject(sf::Drawable* renderObject)
{
	m_RenderObjects.back().push_back(renderObject);
}

void RenderManager::RemoveRenderObject(const sf::Drawable* renderObject)
{
	for (auto iter = m_RenderObjects.back().begin(); iter != m_RenderObjects.back().end(); )
	{
		if (*iter == renderObject)
		{
			iter = m_RenderObjects.back().erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void RenderManager::PushRenderGroup()
{
	m_RenderObjects.emplace_back();
}

void RenderManager::PopRenderGroup()
{
	m_RenderObjects.pop_back();
}
