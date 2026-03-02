#include "Enemy.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Engine/Renderer/FrameTimer.h"
#include "../Player/Player.h"

void Enemy::Chase()
{
	if (m_health > 0)
	{
        m_targetLocation = m_player->GetPosition() + sf::Vector2f(0.0f, -32.0f);

        //Get NPC's current location
        sf::Vector2f currentPosition = GameObjectWithAnimatedSprite::GetPosition();

        //Calculate vector from NPC's current position to target point
        sf::Vector2f faceDirection = m_targetLocation - currentPosition;

        //Calculate the distance (L2-norm) between current and target positions
        float distance = sqrt(faceDirection.x * faceDirection.x + faceDirection.y * faceDirection.y);

        if (m_detectionRadius > distance)
        {
            if (GetCurrentAnimation() != WALK && AnimationFinished() || GetCurrentAnimation() == IDLE)
            {
                SetCurrentAnimation(WALK);
            }

            //If distance is less than displacement to cover in this frame
            if (distance < m_moveSpeed)
            {
                //That means this NPC has reached destination
                GameObjectWithAnimatedSprite::SetPosition(m_targetLocation);
            }
            else
            {
                float angle = atan2(faceDirection.y, faceDirection.x);

                //Calculate movement vector
                sf::Vector2f unitMoveVector = sf::Vector2f(cos(angle), sin(angle));
                sf::Vector2f totalMoveVector = unitMoveVector * m_moveSpeed;

                ClampDirection(totalMoveVector);

                IncrementPosition(totalMoveVector);

                // Flip the enemy depending on the player position
                if (totalMoveVector.x > 0)
                {
                    FlipX(false);
                }
                else if (totalMoveVector.x < 0)
                {
                    FlipX(true);
                }
            }
        }
        else
        {
            SetCurrentAnimation(IDLE);
        }

        // Update the collision box's location.
        m_collisionRect.left = GetPosition().x - (m_enemySize.x / 2.f);
        m_collisionRect.top = GetPosition().y - (m_enemySize.y / 2.f);
	}
}

void Enemy::CheckCollisions()
{
	m_collided = CollidesWith(*m_player);

	if (m_collided && m_health > 0)
	{
		m_player->DoDamage(m_damage);
	}
}

bool Enemy::CheckCollisionWithTile(size_t tile, std::map<size_t, BoxCollider2D>& collisionLayer)
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


void Enemy::CheckWorldCollisions(size_t tile, std::map<size_t, BoxCollider2D>& collisionLayer)
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

void Enemy::DefineHitObjects(int collidedTile)
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

void Enemy::ClampDirection(sf::Vector2f& directionVector) const
{
    // Horizontal axis
   // --- Horizontal axis ---
   // Cannot move left
    if (m_hitObject.left > 0)
    {
        // Cannot move left
        if (directionVector.x < 0)
        {
            directionVector.x = 0;
        }
    }
    // Cannot move right
    if (m_hitObject.top > 0)
    {
        // Cannnot move right
        if (directionVector.x > 0)
        {
            directionVector.x = 0;
        }
    }

    // --- Vertical axis ---
    // Cannot move up
    if (m_hitObject.width > 0)
    {
        if (directionVector.y < 0)
        {
            directionVector.y = 0;
        }
    }
    // Cannot move down
    if (m_hitObject.height > 0)
    {
        if (directionVector.y > 0)
        {
            directionVector.y = 0;
        }
    }
}

void Enemy::TakeDamage(int damageTaken)
{
    m_health -= damageTaken;
    if (m_health > 0)
    {
        SetCurrentAnimation(HIT);
        m_player->IncreaseScore(m_damagedPoints);
    }
    else
    {
        SetCurrentAnimation(DEATHDAMAGE);
        m_player->IncreaseScore(m_killedPoints);
    }
}

bool Enemy::IsDead()
{
	if (m_health <= 0 && AnimationFinished())
	{
        return true;

	}
    else
    {
        return false;
    }
}

int Enemy::GetDamage()
{
	return m_damage;
}

int Enemy::GetHealth()
{
	return m_health;
}

void Enemy::SetHealth(int health)
{
	m_health = health;
}