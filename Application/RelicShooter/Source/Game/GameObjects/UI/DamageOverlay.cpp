#include "DamageOverlay.h"

#include <iso646.h>

#include "../../DebugHandler.hpp"
#include "../../../Engine/Renderer/FrameTimer.h"
#include "../../../Engine/Renderer/RenderManager.h"
#include "../../../Engine/Renderer/WindowManager.h"
#include "../../../Engine/System/Assets/AssetManager.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../Player/Player.h"

DamageOverlay::~DamageOverlay()
{
	C_SysContext::Get<RenderManager>()->RemoveUIRenderObject(&m_overlaySprite);
}

void DamageOverlay::Initialise(Player* player)
{
	m_previousHealth = player->GetHealth();
	m_previousSpeed = player->GetMovementSpeed();

	const sf::Vector2u windowSize = C_SysContext::Get<WindowManager>()->GetWindow().getSize();
	m_windowWidth = windowSize.x;
	m_windowHeight = windowSize.y;

	const sf::Texture& texture = C_SysContext::Get<AssetManager>()->GetTexture("ui/PlayerEffectOverlay.png");
	const sf::Vector2u textureSize = texture.getSize();

	m_overlaySprite.setTexture(texture);
	m_overlaySprite.setPosition({ 0, 0 });
	m_overlaySprite.setScale({
		static_cast<float>(m_windowWidth) / static_cast<float>(textureSize.x),
		static_cast<float>(m_windowHeight) / static_cast<float>(textureSize.y)
	});
	
	FadeOverlay();

	// Add to the renderer
	C_SysContext::Get<RenderManager>()->AddUIRenderObject(&m_overlaySprite);
}

void DamageOverlay::Update(Player* player)
{
	ChangeFadeValue();
	CheckFadeBounds();
	FadeOverlay();

	if (!StartFadeProcess(player))
	{
		return;
	}

	// Start fading processes
	if (m_currentState != FadingIn && m_opacityValue < m_maxFadeValue)
	{
		// Start fading in process
		m_currentState = FadingIn;
	}

}

void DamageOverlay::CheckFadeBounds()
{
	// Stop the fade process if the value has reached its minimum fade
	if (m_currentState == FadingOut && m_opacityValue <= 0)
	{
		m_currentState = NotFading;
		m_currentFadeType = None;
	}

	// Reverse fade process once hit its maximum value
	if (m_opacityValue >= m_maxFadeValue)
	{
		m_currentState = FadingOut;
	}
}

bool DamageOverlay::StartFadeProcess(Player* player)
{
	bool startFadeProcess = false;
	// Damage
	if (m_previousHealth > player->GetHealth())
	{
		m_currentFadeType = Damage;
		startFadeProcess = true;
	}

	// Heal
	if (m_previousHealth < player->GetHealth())
	{
		m_currentFadeType = Heal;
		startFadeProcess = true;
	}

	// Speed
	if (m_previousSpeed < player->GetMovementSpeed())
	{
		m_currentFadeType = Speed;
		startFadeProcess = true;
	}
	m_previousHealth = player->GetHealth();
	m_previousSpeed = player->GetMovementSpeed();

	return startFadeProcess;
}

void DamageOverlay::ChangeFadeValue()
{
	if (m_currentState == FadingOut)
	{
		m_opacityValue -= m_maxFadeValue / (m_fadeOutSpeed * 60.f);
		// Clamp to no lower than 0
		m_opacityValue = std::max(m_opacityValue, 0.f);
	}

	if (m_currentState == FadingIn)
	{
		m_opacityValue += m_maxFadeValue / (m_fadeInSpeed * 60.f);
		// Clamp to no larger than 1
		m_opacityValue = std::min(m_opacityValue, 1.f);
	}
}

void DamageOverlay::FadeOverlay()
{
	m_overlaySprite.setColor({ 
		m_colorTypes[m_currentFadeType].r,
		m_colorTypes[m_currentFadeType].g,
		m_colorTypes[m_currentFadeType].b,
		static_cast<sf::Uint8>(255 * m_opacityValue)

	});
}
