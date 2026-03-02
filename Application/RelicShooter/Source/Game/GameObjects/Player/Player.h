#pragma once

#include <chrono>
#include "../../../Engine/Physics/BoxCollider2D.h"
#include "../BaseGameObjects/GameObjectWithAnimatedSprite.h"
#include "../UI/ReloadCharacter.h"

class RayCastLine;
class BaseWeapon;

struct PlayerStats
{
    // Speed
    const float SpeedBoostMultipler = 3.f;
    const float SpeedBoostTime = 2.5f;                  // Measured in seconds
    const float WalkingSpeedMultiplier = 3.5f;
    const float RunningSpeedMultiplier = 2.5f;
    const float DashSpeedMultiplier = 2.f;

    float WalkingSpeed = WalkingSpeedMultiplier;
    float RunningSpeed = WalkingSpeed * RunningSpeedMultiplier;
    float DashSpeed = RunningSpeed * DashSpeedMultiplier;

    // Health
    int Health = 100;                                   // Current health
    const int MaxHealth = 100.f;
    const float DamageCooldown = 1.5f;                  // Damage taken per x seconds

    // Dash
    const float DashReactionTime = 0.2f;                // Measured in seconds
    const float DashMaxTime = 0.2f;                     // Measured in seconds

    // Stamina
    float Stamina = 100.f;                              // Current stamina 
    const float StaminaRegen = 20.f;                    // Adds x every second
    const float StaminaRestTime = 1.2f;                 // Seconds required to wait until stamina can regen 
    const float MaxStamina = 100.f;
    // Stamina Cost
    const float DashStaminaCost = 25.f;                 // Subtracts 50 stamina everytime dash is called
    const float RunningStaminaCost = 25.f;       // Subtracts x every second

    // Ammo
    int Ammo = 120.f;                                   // Current ammo count
    int MaxAmmo = 120.f;
};
struct PointSystem
{
    int Points = 0;
    int PointMultiplier = 10;                           // Multiplies by points and is reduced over time
	const float PointReductionTime = 20.f;              // Measured in seconds, reduces multiplier by 1	
};
struct CameraInfo
{
    const float ShakeDuration = 0.4f;                   // Measured in seconds
    const float ShakeAmount = 7;                        // Move the camera in pixels
    
    const float DesiredZoom = 0.8f;                     // Default camera zoom
    const float ScopeZoom = 0.6f;                       // Scope zoom
    const float MaxDeltaZoom = 0.025f;                  // Max camera zoom change per frame

};

class Player : public GameObjectWithAnimatedSprite, public BoxCollider2D
{
public:
	Player() = default;
    ~Player() override;

    // --- Override functions ---
    void Initialise() override;
    void Update() override;
    sf::Vector2f GetPosition() override;

    // --- Weapons ---
    void PickupWeapon(BaseWeapon* weapon);
	BaseWeapon* GetCurrentWeapon() { return m_currentWeapon; }
	BaseWeapon* GetStashedWeapon() { return m_stashedWeapon; }

    // --- Raycast ---
    void UpdateRaycast(RayCastLine* raycast);

    // --- Collisions ---
    void CheckWorldCollisions(size_t tile, std::map<size_t, BoxCollider2D>& collisionLayer);

    // --- Camera ---
    void CameraMovement();
    void StopCameraMovement();

    // --- Player stats ---
	// Health
    int GetHealth() const;
	int GetMaxHealth() const;
    void DoDamage(int damage);
    bool IsDead();
    void IncreaseHealth(int health);
	// Stamina
    float GetStamina() const;
	float GetMaxStamina() const;
	float GetDashStaminaCost() const;
	int GetRunningStaminaCost() const;
	// Ammo
    int GetAmmoCount() const;
    int GetMaxAmmo() const;
    void IncreaseAmmo(int ammo);
	// Score
	int GetScore() const;
	void IncreaseScore(int scoreNumber);
    // Speed
    int GetMovementSpeed() const;
    void IncreaseMovementSpeed();

private:
    // --- Movement ---
	inline void Movement();
    inline void CheckSpeedBoost();
    inline void RecalculateMovementSpeed();
    inline void Direction();
    inline void UpdateCollisionPosition();
    // --- Dash ---
    inline void InitialisePlayerDash();
    inline void PlayerDash();
    // --- Camera ---
    inline void StartCameraShake();
    inline void CameraShake();
    // --- Randomise function ---
    inline int Randomise(int min, int max);
    // --- Stamina ---
    inline void ReloadStamina();
    // --- Collisions ---
    inline void DefineHitObjects(int collidedTile);
    inline bool CheckCollisionWithTile(size_t tile, std::map<size_t, BoxCollider2D>& collisionLayer);
    inline void ClampDirection(sf::Vector2f& directionVector) const;
	// --- Health ---
	inline void CheckPlayerHealth();
    // --- Point System ---
    inline void AdjustPointMultiplier();
	
    // --- Weapons ---
    inline void SwitchWeapons();
    inline void UpdateReloadCharacter();
    inline void UpdateWeapon();
    inline void WeaponInputs();
	inline void WeaponScope();

private:
    // Window context
    size_t m_windowWidth;
    size_t m_windowHeight;

    // Player speed boost
    bool m_hasSpeedBoostEffect = false;
    std::chrono::time_point<std::chrono::system_clock> m_speedBoostStartTime;

    // Player stats
    PlayerStats m_playerStats;
    PointSystem m_pointSystem;
    CameraInfo m_cameraInfo;

    // Points
    std::chrono::time_point<std::chrono::system_clock> m_pointStartTime;

    // Camera controls
    const sf::Vector2f m_cameraOffset = { 100, 100 };
	float m_currentZoom;
    sf::Vector2i m_randomCameraMovement = {0, 0};
    bool m_enableCameraOffset = true;

    // Camera shake
    bool m_isCameraShaking = false;
    std::chrono::time_point<std::chrono::system_clock> m_shakeStartTime;

    // Player size
    const sf::Vector2f m_playerSize = {72, 88};
	
	// Stamina cooldown
	std::chrono::time_point<std::chrono::system_clock> m_staminaRestStartTime;

    // Weapon inventory
    BaseWeapon* m_currentWeapon = nullptr;
    BaseWeapon* m_stashedWeapon = nullptr;

    // Reload UI
    ReloadCharacter m_reloadCharacter;
	
	// Damage control
	std::chrono::time_point<std::chrono::system_clock> m_damageStartTime;

    // --------------------------LEFT--------RIGHT--------UP--------DOWN
    sf::IntRect m_hitObject = {0, 0, 0, 0};

    // Dash timer and control
	std::chrono::time_point<std::chrono::system_clock> m_dashStartTime;
    float m_previousMovementX = 0.f;
    float m_previousMovementY = 0.f;

    // Player movement states used for animations
    enum PlayerStates
    {
	    Idle, 
        Walking, 
        Running,
        Dash,
        Holo,
        Teleport,
        Death,
        STATE_MAX
    };

    // Keep track of the current player state
    PlayerStates m_playerState = Idle;

    // Array of animation names
    const char* m_animationImageName[STATE_MAX] = 
    {
        "spr_jimmy_idle",
        "spr_jimmy_walk",
        "spr_jimmy_sprint",
		"spr_jimmy_dash",
		"spr_jimmy_holo",
        "spr_jimmy_teleport_out",
		"spr_jimmy_death"
    };
};
