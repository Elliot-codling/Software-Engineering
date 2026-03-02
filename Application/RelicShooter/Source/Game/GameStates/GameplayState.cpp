#include "GameplayState.h"

#include "MainMenuState.h"
#include "../../Engine/Renderer/RenderManager.h"
#include "../Input/InputWrapper.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../GameObjects/Weapons/Rifle.h"
#include "../GameObjects/Weapons/Shotgun.h"
#include "../GameObjects/BaseGameObjects/GameObjectWithSprite.h"

GameplayState::GameplayState(int windowWidth, int windowHeight)
{
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;
}

void GameplayState::Initialise()
{
	// Create player
	m_playerCharacter.Initialise();
	AddGameObject(&m_playerCharacter);

	// Stops the first frame from being in the wrong position
	sf::View& viewPort = C_SysContext::Get<RenderManager>()->GetGameRenderView();
	viewPort.setCenter(m_playerCharacter.GetPosition());

	// TODO: Delete this sprite below
	GameObjectWithSprite* sprite = new GameObjectWithSprite();
	sprite->CreateSprite();
	sprite->Initialise();
	AddGameObject(sprite);

	m_crosshair.Initialise();
	AddGameObject(&m_crosshair);

	// TODO: Will be removed
	for (int i = 0; i < 3; i++)
	{
		BaseWeapon* baseWeapon = nullptr;
		if (i % 2 == 0)
		{
			LOG("Created shotgun")
			baseWeapon = new Shotgun();
		}
		else
		{
			LOG("Created rifle")
			baseWeapon = new Rifle();
		}
		
		baseWeapon->Initialise();
		baseWeapon->SetPosition({ 0, static_cast<float>(i) * 300 });
		AddGameObject(baseWeapon);
		m_weapons.emplace_back(baseWeapon);
	}
	
}

void GameplayState::Update()
{
	GameState::Update();

	m_crosshair.ReloadCrosshair(m_playerCharacter.GetCurrentWeapon());

	// TODO: Test of having multiple weapons in the game
	for (BaseWeapon* weapon : m_weapons)
	{
		sf::Vector2f distanceToWeapon = m_playerCharacter.GetPosition() - weapon->GetPosition();
		float distance = sqrt((distanceToWeapon.x * distanceToWeapon.x) + (distanceToWeapon.y * distanceToWeapon.y));
		weapon->SetBeingHighlighted(false);
		if (distance < 120.f)
		{
			weapon->SetBeingHighlighted(true);
			DigitalInput* xInput = GetDigitalInput(E_DigitalInput_X);
			if (xInput->GetHoldTime() > 1.f && xInput->IsDown())
			{
				m_playerCharacter.PickupWeapon(weapon);
			}
		}
	}
	

	
}

void GameplayState::FixedUpdate()
{
	GameState::FixedUpdate();

	// Return to main menu if start is pressed
	if (GetDigitalInput(E_DigitalInput_Start)->IsDown())
	{
		MainMenuState* mainMenuState = new MainMenuState(m_windowWidth, m_windowHeight);
		C_SysContext::Get<GameStateManager>()->QueueGameState(mainMenuState);

		sf::Window& window = C_SysContext::Get<WindowManager>()->GetWindow();
		window.setMouseCursorVisible(true);
	}
}
