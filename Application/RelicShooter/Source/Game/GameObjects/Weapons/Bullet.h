#pragma once
#include "../../../Engine/Physics/CircleCollider2D.h"
#include "../BaseGameObjects//GameObjectWithAnimatedSprite.h"

class TileMap;
class Enemy;

namespace BulletTypes
{
	enum Type
	{
		Blue,
		Red,
		TYPE_MAX
	};
}

class Bullet : public GameObjectWithAnimatedSprite, public CircleCollider2D
{
public:
	Bullet() = default;
	~Bullet() override = default;

	void Initialise(BulletTypes::Type bulletType, std::vector<Enemy*>* enemyVector, TileMap* collisionMap);
	void Update() override;
	void SetBulletDirectionVector();

protected:
	// --- Frametime ---
	void CalculateAnimationFPS();
	// --- Movement ---
	void Movement();
	void UpdateCollisionMovement();
	// --- Collisions ---
	void CheckOutOfBounds();
	void CheckEnemyCollisions();
	void CheckWorldCollisions();

protected:
	// World collisions
	TileMap* m_collisionTilemap = nullptr;
	
	// Window info
	size_t m_windowWidth;
	size_t m_windowHeight;
	float m_aspectRatio;

	sf::Vector2f m_directionVector = {0, 0};

	float m_bulletSpeed;
	float m_bulletFPS;

	BulletTypes::Type m_bulletType;
	
	const char* m_bulletFilenames[BulletTypes::TYPE_MAX]
	{
		"sprites/weapons/bullets/spr_bullet_blue.xml",
		"sprites/weapons/bullets/spr_bullet_red.xml"
	};

private:
	// Enemies
	std::vector<Enemy*>* m_enemies = nullptr;

	// Damage value based on the bullet type
	int m_damageValue[BulletTypes::TYPE_MAX] = 
	{
		20,	// Blue
		30	// Red
	};
};

