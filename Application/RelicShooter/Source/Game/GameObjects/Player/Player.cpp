#include "Player.h"

#include "../../Input/InputWrapper.h"
#include "../../../Engine/Renderer/WindowManager.h"
#include "../../../Engine/Renderer/RenderManager.h"
#include "../../../Engine/System/GameState/GameState.h"
#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../Weapons/BaseWeapon.h"
#include "../UI/ReloadCharacter.h"
#include <algorithm>
#include <random>

#include "RayCastLine.h"


Player::~Player()
{
    C_SysContext::Get<RenderManager>()->RemoveGameRenderView();
}

void Player::Initialise()
{
    GameObjectWithAnimatedSprite::Initialise();

    const sf::Window& window = C_SysContext::Get<WindowManager>()->GetWindow();
    m_windowWidth = window.getSize().x;
    m_windowHeight = window.getSize().y;

    // Load sprite sheet
    AddSpriteSheet("sprites/characters/spr_jimmy.xml");
    // Define animations
    AddAnimation(Idle, m_animationImageName[Idle], 10, true);
    AddAnimation(Walking, m_animationImageName[Walking], 10, true);
    AddAnimation(Running, m_animationImageName[Running], 10, true);
    AddAnimation(Dash, m_animationImageName[Dash], 10, true);
    AddAnimation(Holo, m_animationImageName[Holo], 10, true);
    AddAnimation(Teleport, m_animationImageName[Teleport], 10, false);
    AddAnimation(Death, m_animationImageName[Death], 10, false);

    SetCurrentAnimation(Idle);

    // Scale player
    /* NOTE:
     * Each player frame is much larger than what is shown
     * Therefore the collision box is seperate to the player size
     */
    SetScaleInPixels({128, 128});
    m_collisionRect = {0, 0, m_playerSize.x, m_playerSize.y};

    // Setup reloading bar
    m_reloadCharacter.Initialise();
    C_SysContext::Get<GameStateManager>()->GetCurrentGameState()->AddGameObject(&m_reloadCharacter);

    // Set camera zoom
    m_currentZoom = m_cameraInfo.DesiredZoom;
    sf::View& viewPort = C_SysContext::Get<RenderManager>()->GetGameRenderView();
    viewPort.setSize({
        1920.f * m_cameraInfo.DesiredZoom,
		1080.f * m_cameraInfo.DesiredZoom }
        );
    viewPort.setCenter(GetPosition());

    // Start the timer for point system
    m_pointStartTime = std::chrono::system_clock::now();
}

void Player::Update()
{
    GameObjectWithAnimatedSprite::Update();
    // Update player state
    SetCurrentAnimation(m_playerState);

    UpdateCollisionPosition();
    Movement();
    CheckSpeedBoost();
    RecalculateMovementSpeed();
    PlayerDash();
    Direction();
    ReloadStamina();
    SwitchWeapons();
    UpdateReloadCharacter();
    CheckPlayerHealth();
    WeaponScope();
    AdjustPointMultiplier();
    CameraShake();

    if (m_currentWeapon == nullptr)
    {
        return;
    }

    UpdateWeapon();
    WeaponInputs();
}

void Player::PickupWeapon(BaseWeapon* weapon)
{
    // Ignore this function if the player already has a weapon
    // Or if the player already has this weapon stashed
    if (m_currentWeapon != nullptr || m_stashedWeapon == weapon)
    {
        return;
    }
    m_currentWeapon = weapon;
    m_currentWeapon->SetBeingHeld(true);
}

void Player::UpdateRaycast(RayCastLine* raycast)
{
    raycast->SetVisibility(false);
    if (m_currentWeapon == nullptr)
    {
        return;
    }

    const float scope = GetAnalogueInput(E_AnalogueInput_LeftTrigger)->GetValue();
    if (scope <= 0)
    {
        return;
    }

    raycast->SetVisibility(true);
}

void Player::CheckWorldCollisions(size_t tile, std::map<size_t, BoxCollider2D>& collisionLayer)
{
    // Need to check collisions around the player
    // NOTE: This is not ideal.
    size_t tilesAroundPlayer[8] = 
    {
        // LEFT AND RIGHT
		tile - 1,
        tile + 1,
        // UP AND DOWN
        tile - 60,
        tile + 60,
    };

    int collidedTile = -1;
    m_hitObject = { 0, 0, 0, 0 };
    for (size_t index = 0; index < std::size(tilesAroundPlayer); index++)
    {
        if (CheckCollisionWithTile(tilesAroundPlayer[index], collisionLayer))
        {
            collidedTile = static_cast<int>(index);
            DefineHitObjects(collidedTile);
        }
    }
}

int Player::GetHealth() const
{
    return m_playerStats.Health;
}

int Player::GetMaxHealth() const
{
    return m_playerStats.MaxHealth;
}

float Player::GetStamina() const
{
    return m_playerStats.Stamina;
}

float Player::GetMaxStamina() const
{
    return m_playerStats.MaxStamina;
}

float Player::GetDashStaminaCost() const
{
    return m_playerStats.DashStaminaCost;
}

int Player::GetRunningStaminaCost() const
{
    return m_playerStats.RunningStaminaCost / 60.f;
}

int Player::GetAmmoCount() const
{
    return m_playerStats.Ammo;
}

int Player::GetMaxAmmo() const
{
    return m_playerStats.MaxAmmo;
}

void Player::IncreaseAmmo(int ammo)
{
    m_playerStats.Ammo += ammo;
}

int Player::GetScore() const
{
    return m_pointSystem.Points;
}

void Player::IncreaseScore(int scoreNumber)
{
    m_pointSystem.Points += scoreNumber * m_pointSystem.PointMultiplier;
}

int Player::GetMovementSpeed() const
{
    return m_playerStats.WalkingSpeed;
}

void Player::IncreaseMovementSpeed()
{
    m_hasSpeedBoostEffect = true;
    m_speedBoostStartTime = std::chrono::system_clock::now();
}

void Player::DoDamage(int damage)
{
    std::chrono::duration<float> duration = std::chrono::system_clock::now() - m_damageStartTime;
    if (duration.count() < m_playerStats.DamageCooldown)
    {
        return;
    }
    m_playerStats.Health -= damage;
    m_playerStats.Health = std::max(m_playerStats.Health, 0);

    m_damageStartTime = std::chrono::system_clock::now();
    StartCameraShake();
}

bool Player::IsDead()
{
    if (m_playerStats.Health <= 0 && AnimationFinished())
    {
        return true;
    }
    return false;
}

void Player::IncreaseHealth(int health)
{
    // Prevent adding health if the player is already dead
    if (m_playerStats.Health <= 0)
    {
        return;
    }
    m_playerStats.Health += health;
    m_playerStats.Health = std::min<int>(m_playerStats.Health, m_playerStats.MaxHealth);
}

sf::Vector2f Player::GetPosition()
{
    const sf::Vector2f tileOffset = { 0, 32 };
	return GameObjectWithAnimatedSprite::GetPosition() + tileOffset;
}

void Player::Movement()
{
    const float movementX = GetAnalogueInput(E_AnalogueInput_ThumbLX)->GetValue();
    const float movementY = GetAnalogueInput(E_AnalogueInput_ThumbLY)->GetValue();
    const bool running = GetDigitalInput(E_DigitalInput_A)->IsDown();

    // Prevent code from running if in these states
    switch (m_playerState)
    {
    case Holo:
    case Teleport:
    case Death:
    case Dash:
        return;

    default:
        break;
    }
    
    if (movementX == 0 && movementY == 0)
    {
        // Change to idle if not moving and the current state is walking or running
        if (m_playerState == Walking || m_playerState == Running)
        {
            m_playerState = Idle;
        }
        return;
    }

	// Reduce stamina if running, cannot run if out of stamina
    m_playerState = Walking;
    float speed = m_playerStats.WalkingSpeed;

    if (running && m_playerStats.Stamina - (m_playerStats.RunningStaminaCost / 60.f) >= 0.f)
    {
        m_playerState = Running;
        speed = m_playerStats.RunningSpeed;
    }

    if (!m_hasSpeedBoostEffect && running && m_playerStats.Stamina - (m_playerStats.RunningStaminaCost / 60.f) >= 0.f)
    {
        m_playerStats.Stamina -= m_playerStats.RunningStaminaCost / 60.f;
        // Ensure player stamina hits zero
        if (m_playerStats.Stamina - (m_playerStats.RunningStaminaCost / 60.f) < 0.f)
        {
            m_playerStats.Stamina = 0.f;
        }
        
    }

    sf::Vector2f directionVector = { speed * movementX, speed * movementY };
    ClampDirection(directionVector);

    // Change the speed based on walking or running
    IncrementPosition(directionVector);
}

void Player::CheckSpeedBoost()
{
    if (!m_hasSpeedBoostEffect)
    {
        return;
    }

    std::chrono::duration<float> duration = std::chrono::system_clock::now() - m_speedBoostStartTime;
    if (duration.count() >= m_playerStats.SpeedBoostTime)
    {
		m_hasSpeedBoostEffect = false;
    }
}

void Player::RecalculateMovementSpeed()
{
    m_playerStats.WalkingSpeed = m_playerStats.WalkingSpeedMultiplier;

    if (m_hasSpeedBoostEffect)
    {
        m_playerStats.WalkingSpeed *= m_playerStats.SpeedBoostMultipler;
        m_playerStats.RunningSpeed = m_playerStats.WalkingSpeed;
        m_playerStats.DashSpeed = m_playerStats.WalkingSpeed;
    }
    else
    {
        m_playerStats.RunningSpeed = m_playerStats.WalkingSpeed * m_playerStats.RunningSpeedMultiplier;
        m_playerStats.DashSpeed = m_playerStats.RunningSpeed * m_playerStats.DashSpeedMultiplier;
    }
}

void Player::Direction()
{
    const float movementX = GetAnalogueInput(E_AnalogueInput_ThumbLX)->GetValue();
    const float rightStickX = GetAnalogueInput(E_AnalogueInput_ThumbRX)->GetValue();

    // Prevent code from running if in these states
    switch (m_playerState)
    {
    case Holo:
    case Teleport:
    case Death:
    case Dash:
        return;

    default:
        break;
    }

    // Flip the player depending on the player direction
    if (movementX > 0)
    {
        FlipX(false);
    }
    else if (movementX < 0)
    {
        FlipX(true);
    }

    // Fip the player depending on where the right stick is
    if (rightStickX > 0)
    {
        FlipX(false);
    }
    else if (rightStickX < 0)
    {
        FlipX(true);
    }
    
}

void Player::UpdateCollisionPosition()
{
    // Update the player collision rect
    m_collisionRect.left = GetPosition().x - (m_playerSize.x / 2.f);
    m_collisionRect.top = GetPosition().y - (m_playerSize.y / 2.f);
}

void Player::InitialisePlayerDash()
{
    m_playerStats.Stamina -= m_playerStats.DashStaminaCost;

    // Change state and record time
    m_playerState = Dash;
    m_dashStartTime = std::chrono::system_clock::now();

    // Capture last movements of virtual controller
    m_previousMovementX = GetAnalogueInput(E_AnalogueInput_ThumbLX)->GetValue();
    m_previousMovementY = GetAnalogueInput(E_AnalogueInput_ThumbLY)->GetValue();

    // If not moving, go in the direction of the mouse
    if (abs(m_previousMovementX) > 0 || abs(m_previousMovementY) > 0)
    {
        const bool flipCharacter = m_previousMovementX < 0;
        FlipX(flipCharacter);
        return;
    }

	// If the player is not moving, dash in the direction of the right stick
    m_previousMovementX = GetAnalogueInput(E_AnalogueInput_ThumbRX)->GetValue();
    m_previousMovementY = GetAnalogueInput(E_AnalogueInput_ThumbRY)->GetValue();
    // Only really applies to controller
    if (abs(m_previousMovementX) == 0 || abs(m_previousMovementY) == 0)
    {
		m_previousMovementX = IsFlippedX() ? -1.f : 1.f;
    }
	// Normalize the dash direction
	// Consistent dash speed in all directions
	const float magnitude = sqrt((m_previousMovementX * m_previousMovementX) + (m_previousMovementY * m_previousMovementY));

	m_previousMovementX /= magnitude;
    m_previousMovementY /= magnitude;

    const bool flipCharacter = m_previousMovementX < 0;
    FlipX(flipCharacter);
}

void Player::PlayerDash()
{
    DigitalInput* running = GetDigitalInput(E_DigitalInput_A);

    // Start dash state if the button is pressed for 100 ms
    if (running->HasCompletedCycle() && running->GetHoldTime() < m_playerStats.DashReactionTime && m_playerStats.Stamina - m_playerStats.DashStaminaCost >= 0.f && !m_hasSpeedBoostEffect)
    {
		InitialisePlayerDash();
    }

    // Check if dash has finished
    std::chrono::duration<float> dashDuration = std::chrono::system_clock::now() - m_dashStartTime;
    if (m_playerState == Dash && dashDuration.count() >= m_playerStats.DashMaxTime)
    {
        m_playerState = Idle;
    }
    else if (m_playerState == Dash)
    {
        sf::Vector2f directionVector = { m_playerStats.DashSpeed * m_previousMovementX, m_playerStats.DashSpeed * m_previousMovementY };
        ClampDirection(directionVector);
        // Else move player if in dash state
        IncrementPosition(directionVector);
    }
}

void Player::CameraMovement()
{
    const float rightStickX = GetAnalogueInput(E_AnalogueInput_ThumbRX)->GetValue();
    const float rightStickY = GetAnalogueInput(E_AnalogueInput_ThumbRY)->GetValue();

    sf::Vector2f cameraOffset = {0, 0};
    if (m_enableCameraOffset)
    {
		cameraOffset = { m_cameraOffset.x * rightStickX, m_cameraOffset.y * rightStickY };
    }
	// Convert everything to integer for pixel perfect rendering
	const sf::Vector2f position = GetPosition() + cameraOffset;

    // Convert back to float
    sf::View& viewPort = C_SysContext::Get<RenderManager>()->GetGameRenderView();
    viewPort.setCenter(position + static_cast<sf::Vector2f>(m_randomCameraMovement));
}

void Player::StopCameraMovement()
{
    m_enableCameraOffset = false;
}

void Player::StartCameraShake()
{
    m_isCameraShaking = true;
    m_shakeStartTime = std::chrono::system_clock::now();
}

void Player::CameraShake()
{
    // Return if camera is not shaking
    if (!m_isCameraShaking || m_playerStats.Health <= 0)
    {
        return;
    }

    std::chrono::duration<float> duration = std::chrono::system_clock::now() - m_shakeStartTime;
    if (duration.count() >= m_cameraInfo.ShakeDuration)
    {
        m_isCameraShaking = false;
        m_randomCameraMovement = { 0, 0 };
        return;
    }

    m_randomCameraMovement = {
        Randomise(1, m_cameraInfo.ShakeAmount),
        Randomise(1, m_cameraInfo.ShakeAmount)
    };
}

int Player::Randomise(int min, int max)
{
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> dist(min, max);

    return dist(gen);
}

void Player::ReloadStamina()
{
    DigitalInput* runButton = GetDigitalInput(E_DigitalInput_A);
    
    // Cannot regen stamina if on zero for x seconds
    if (runButton->HasCompletedCycle() && m_playerStats.Stamina <= m_playerStats.MaxStamina / 2.f)
    {
        m_staminaRestStartTime = std::chrono::system_clock::now();
    }
    
    // Check if player can start regen process
    std::chrono::duration<float> staminaRestTime = std::chrono::system_clock::now() - m_staminaRestStartTime;
    if (m_hasSpeedBoostEffect || m_playerStats.Stamina < 100.f && !runButton->IsDown() && staminaRestTime.count() >= m_playerStats.StaminaRestTime)
    {
        m_playerStats.Stamina += m_playerStats.StaminaRegen / 60.f;
    }
    
    // Ensure player stamina does not go over max stamina
    m_playerStats.Stamina = std::min(m_playerStats.Stamina, m_playerStats.MaxStamina);
}

void Player::DefineHitObjects(int collidedTile)
{
    // Define where the player can move to
    switch (collidedTile)
    {
    case 0:
        // Left tile
        m_hitObject.left = 1;
        break;

    case 1:
        // Right tile
        m_hitObject.top = 1;
        break;

    case 2:
        // Top tile
        m_hitObject.width = 1;
        break;

    case 3:
        // Bottom tile
        m_hitObject.height = 1;
        break;

    default:
        m_hitObject = { 0, 0, 0, 0 };
        break;
    }
}

bool Player::CheckCollisionWithTile(size_t tile, std::map<size_t, BoxCollider2D>& collisionLayer)
{
    if (collisionLayer.find(tile) != collisionLayer.end())
    {
        BoxCollider2D& rect = collisionLayer.at(tile);

        if (rect.CollidesWith(*this))
        {
            return true;
        }
    }
    return false;
}

void Player::ClampDirection(sf::Vector2f& directionVector) const
{
	// --- Horizontal axis ---
	// Cannot move left
    if (m_hitObject.left > 0)
    {
        // Cannot move left
        directionVector.x = std::max<float>(directionVector.x, 0);
    }
    // Cannot move right
    if (m_hitObject.top > 0)
    {
        // Cannnot move right
        directionVector.x = std::min<float>(directionVector.x, 0);
    }

    // --- Vertical axis ---
    // Cannot move up
    if (m_hitObject.width > 0)
    {
        directionVector.y = std::max<float>(directionVector.y, 0);
    }
    // Cannot move down
    if (m_hitObject.height > 0)
    {
    	directionVector.y = std::min<float>(directionVector.y, 0);
    }
}

void Player::CheckPlayerHealth()
{
    if (m_playerStats.Health > 0)
    {
        return;
    }

    m_enableCameraOffset = false;
    m_playerState = Death;
}

void Player::AdjustPointMultiplier()
{
    std::chrono::duration<float> duration = std::chrono::system_clock::now() - m_pointStartTime;
    if (m_pointSystem.PointMultiplier > 1 && duration.count() >= m_pointSystem.PointReductionTime)
    {
        m_pointSystem.PointMultiplier--;
        m_pointStartTime = std::chrono::system_clock::now();
    }
}

void Player::SwitchWeapons()
{
	// Due to this function only updating every 16.666ms sometimes it misses when a key has been pressed
    // Therefore check when a key has finished a cycle 

    DigitalInput* switchWeaponsKey = GetDigitalInput(E_DigitalInput_Y);
    if (!switchWeaponsKey->HasCompletedCycle())
    {
        return;
    }

    // If the y button has completed a cycle
    // Set current weapon invisible and stop the reloading process
    if (m_currentWeapon != nullptr)
    {
        m_currentWeapon->StopReload();
		m_currentWeapon->SetVisible(false);
    }
    // Swap the weapon contents over
    std::swap(m_currentWeapon, m_stashedWeapon);

    // Make the new weapon visible
    if (m_currentWeapon != nullptr)
    {
        m_currentWeapon->SetVisible(true);
    }
}

void Player::UpdateReloadCharacter()
{
    const sf::Vector2f characterOffset = { 0, 50 };
    m_reloadCharacter.SetPosition(GetPosition() + characterOffset);
    m_reloadCharacter.UpdateReloadState(m_currentWeapon);
}

void Player::UpdateWeapon()
{
    const float rightStickX = GetAnalogueInput(E_AnalogueInput_ThumbRX)->GetValue();
    const float rightStickY = GetAnalogueInput(E_AnalogueInput_ThumbRY)->GetValue();

	// Set weapon position to player position
    m_currentWeapon->SetPosition(GetPosition());

    // Rotate the weapon
    m_currentWeapon->FlipX(false);
    if (GetCurrentAnimation() == Dash && rightStickX < 0)
    {
        m_currentWeapon->FlipX(!IsFlippedX());
    }
    else if (GetCurrentAnimation() == Dash && rightStickX > 0)
    {
        m_currentWeapon->FlipX(IsFlippedX());
    }

    m_currentWeapon->Reload(m_playerStats.Ammo);
    
    // Only really applies to using a controller
    if (rightStickX == 0 && rightStickY == 0)
    {
        m_currentWeapon->SetAngle(0);
        m_currentWeapon->FlipY(false);
        m_currentWeapon->FlipX(IsFlippedX());
		// Ignore rest of function if the right stick is not being used
        return;
    }

    // Move the direction of the weapon to the right stick
	m_currentWeapon->Direction({0, 0});
}

void Player::WeaponInputs()
{
    // Prevent code from running while in these states
	switch (m_playerState)
    {
    case Holo:
    case Teleport:
    case Death:
        return;

    default:
        break;
    }

    // Start a reload sequence
    DigitalInput* reloadWeapon = GetDigitalInput(E_DigitalInput_X);
    if (reloadWeapon->HasCompletedCycle() && reloadWeapon->GetHoldTime() < 0.2f)
    {
        m_currentWeapon->InitaliseReload();
    }

    // Fire current weapon
    const float fireWeapon = GetAnalogueInput(E_AnalogueInput_RightTrigger)->GetValue();
    if (fireWeapon > 0)
    {
        m_currentWeapon->Fire();
    }

    // Drop current weapon
    if (GetDigitalInput(E_DigitalInput_B)->IsDown() && m_currentWeapon != nullptr)
    {
        m_currentWeapon->StopReload();
        m_currentWeapon->SetBeingHeld(false);
        m_currentWeapon = nullptr;
    }
}

void Player::WeaponScope()
{
    const float scope = GetAnalogueInput(E_AnalogueInput_LeftTrigger)->GetValue();
    const sf::Vector2f standardSize = {1920 * m_cameraInfo.DesiredZoom, 1080 * m_cameraInfo.DesiredZoom };
    sf::View& viewPort = C_SysContext::Get<RenderManager>()->GetGameRenderView();
    
    if (scope > 0 && m_currentWeapon != nullptr)
    {
        if (m_currentZoom > m_cameraInfo.ScopeZoom)
        {
            m_currentZoom -= m_cameraInfo.MaxDeltaZoom;
        }
    
        // Set scope zoom
        viewPort.setSize({
            1920.f * m_currentZoom,
            1080.f * m_currentZoom }
            );
        return;
    }
    
    // Return if the zoom matches the required screen size
    if (viewPort.getSize() == standardSize)
    {
        return;
    }
    
    // Increase zoom if the current zoom level is smaller than what is required
    if (m_cameraInfo.DesiredZoom > m_currentZoom)
    {
        m_currentZoom += m_cameraInfo.MaxDeltaZoom;
    }
    
    // Set camera zoom
    viewPort.setSize({
        1920.f * m_currentZoom,
        1080.f * m_currentZoom }
        );
}
