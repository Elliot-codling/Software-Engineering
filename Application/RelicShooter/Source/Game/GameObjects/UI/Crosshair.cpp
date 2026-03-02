#include "Crosshair.h"

#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Engine/Renderer/WindowManager.h"
#include "../../Input/InputWrapper.h"
#include "../../../Engine/Renderer/RenderManager.h"
#include "../Weapons/BaseWeapon.h"

void Crosshair::Initialise()
{
	SetUIObject(true);
	GameObjectWithAnimatedSprite::Initialise();

	sf::Window& window = C_SysContext::Get<WindowManager>()->GetWindow();
	m_windowWidth = window.getSize().x;
	m_windowHeight = window.getSize().y;

	// Only show crosshair if using keyboard and mouse
	if (GetCurrentInputType() == Keyboard_Mouse)
	{
		AddSpriteSheet("ui/spr_crosshair.xml");
		AddAnimation(Normal, m_animationImageName[Normal], 1, false);
		AddAnimation(Reloading, m_animationImageName[Reloading], 10, false);
		SetCurrentAnimation(Normal);
		SetScaleInPixels({ 64, 64 });

		window.setMouseCursorVisible(false);
	}
}

void Crosshair::Update()
{
	if (GetCurrentInputType() != Keyboard_Mouse)
	{
		return;
	}	

	MoveCrosshair();
}


void Crosshair::MoveCrosshair()
{
	// Get right stick
	const float rightStickX = GetAnalogueInput(E_AnalogueInput_ThumbRX)->GetValue();
	const float rightStickY = GetAnalogueInput(E_AnalogueInput_ThumbRY)->GetValue();

	// Get the viewport
    const sf::View viewPort = C_SysContext::Get<WindowManager>()->GetWindow().getDefaultView(); // this would change to GetUIView in rendermanager if it existed
	const sf::Vector2f viewPortSize = viewPort.getSize();

	// Adjust for camera movement
	const sf::Vector2f cameraPosition = viewPort.getCenter();
	
	// Make (0, 0) to the centre of the screen
	const float mouseX = (rightStickX * (viewPortSize.x / 2.f)) + cameraPosition.x;
	const float mouseY = (rightStickY * (viewPortSize.y / 2.f)) + cameraPosition.y;

	SetPosition({ mouseX, mouseY });
}

void Crosshair::ReloadCrosshair(const BaseWeapon* weapon)
{
	GameObjectWithAnimatedSprite::Update();
	if (weapon == nullptr || GetCurrentInputType() != Keyboard_Mouse)
	{
		if (GetCurrentAnimation() == Reloading)
		{
			SetCurrentAnimation(Normal);
		}
		return;
	}

	const bool weaponIsReloading = weapon->IsWeaponReloading();
	if (weaponIsReloading && GetCurrentAnimation() != Reloading)
	{
		// Set the animation to start
		SetCurrentAnimation(Reloading);
		
		const float numberOfFrames = static_cast<float>(GetNumberOfFrames());
		const float reloadTime = weapon->GetReloadTime();
		SetFPS(numberOfFrames / reloadTime);
		return;
	}

	if (!weaponIsReloading)
	{
		SetCurrentAnimation(Normal);
	}

}
