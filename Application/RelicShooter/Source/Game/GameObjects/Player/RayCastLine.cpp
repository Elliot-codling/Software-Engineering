#include "RayCastLine.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "../../DebugHandler.hpp"
#include "../../../Engine/Renderer/RenderManager.h"
#include "../../../Engine/Renderer/WindowManager.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../Input/InputWrapper.h"
#include "Player.h"

constexpr float RAD_TO_DEG = 180.f / 3.141592f;
constexpr float DEG_TO_RAD = 3.141592f / 180.f;
void RayCastLine::Initialise()
{
	const sf::Window& window = C_SysContext::Get<WindowManager>()->GetWindow();
	m_windowWidth = window.getSize().x;
	m_windowHeight = window.getSize().y;
	m_aspectRatio = static_cast<float>(m_windowWidth) / static_cast<float>(m_windowHeight);

	m_rectangle.setSize({0, m_thickness });
	m_rectangle.setFillColor(m_lineColor);
	m_rectangle.setOrigin(0, m_thickness / 2.f);

	C_SysContext::Get<RenderManager>()->AddRenderObject(&m_rectangle);
}

void RayCastLine::Update(Player* player)
{
	const float rightStickX = GetAnalogueInput(E_AnalogueInput_ThumbRX)->GetValue();
	const float rightStickY = GetAnalogueInput(E_AnalogueInput_ThumbRY)->GetValue();

	// Rotate the weapon to point towards the right stick
	float angle = atan2f(rightStickY, rightStickX * m_aspectRatio);
	if (player->IsFlippedX() && rightStickX == 0 && rightStickY == 0)
	{
		angle -= 180.f * DEG_TO_RAD;
	}

	m_rectangle.setRotation(angle * RAD_TO_DEG);
}

void RayCastLine::SetPosition(sf::Vector2f position)
{
	m_rectangle.setPosition(position);
}

void RayCastLine::SetLength(float length)
{
	m_rectangle.setSize({ length, m_thickness });
}

void RayCastLine::SetVisibility(bool visible)
{
	if (visible)
	{
		m_rectangle.setFillColor(m_lineColor);
	}
	else
	{
		m_rectangle.setFillColor({ 255, 0, 0, 0 });
	}
}