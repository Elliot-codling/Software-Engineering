#include "GameObjectWithAnimatedSprite.h"

#include "../../GameData/GameDataManager.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../DebugHandler.hpp"

void GameObjectWithAnimatedSprite::Initialise()
{
    AnimatedSprite::Initialse(m_lisUIObject);
}

void GameObjectWithAnimatedSprite::Update()
{
    AnimatedSprite::Animate();
}

void GameObjectWithAnimatedSprite::GetPosition(float& px, float& py)
{
    px = AnimatedSprite::getPosition().x;
    py = AnimatedSprite::getPosition().y;
}

sf::Vector2f GameObjectWithAnimatedSprite::GetPosition()
{
    return AnimatedSprite::getPosition();
}

void GameObjectWithAnimatedSprite::SetPosition(float px, float py)
{
    AnimatedSprite::setPosition(px,py);
}

void GameObjectWithAnimatedSprite::SetPosition(sf::Vector2f ppos)
{
    AnimatedSprite::setPosition(ppos);
}

void GameObjectWithAnimatedSprite::IncrementPosition(sf::Vector2f ppos)
{
    AnimatedSprite::move(ppos);
}

float GameObjectWithAnimatedSprite::GetAngle() const
{
    return AnimatedSprite::getRotation();
}

void GameObjectWithAnimatedSprite::SetAngle(float angle)
{
    AnimatedSprite::setRotation(angle);
}

void GameObjectWithAnimatedSprite::IncrementAngle(float angle)
{
    AnimatedSprite::rotate(angle);
}

sf::Vector2f GameObjectWithAnimatedSprite::GetScale() const
{
    return AnimatedSprite::getScale();
}

void GameObjectWithAnimatedSprite::IncrementScale(sf::Vector2f scale)
{
    AnimatedSprite::scale(scale);
}

void GameObjectWithAnimatedSprite::SetScale(sf::Vector2f scale)
{
    AnimatedSprite::setScale(scale);
}

void GameObjectWithAnimatedSprite::SetScaleInPixels(sf::Vector2f scale)
{
    const sf::Vector2i textureSize = AnimatedSprite::GetFrameSize();
    const sf::Vector2f newScale = { scale.x / static_cast<float>(textureSize.x), scale.y / static_cast<float>(textureSize.y) };
	AnimatedSprite::setScale(newScale);
}

void GameObjectWithAnimatedSprite::FlipX(bool flipSprite)
{
    const sf::Vector2f scale = AnimatedSprite::getScale();
    if (flipSprite && scale.x > 0)
    {
        IncrementScale({-1, 1});
    }
    else if (!flipSprite && scale.x < 0)
    {
        IncrementScale({-1, 1});
    }
}

void GameObjectWithAnimatedSprite::FlipY(bool flipSprite)
{
    const sf::Vector2f scale = GetScale();
    if (flipSprite && scale.y > 0)
    {
        IncrementScale({1, -1});
    }
    else if (!flipSprite && scale.y < 0)
    {
        IncrementScale({1, -1});
    }
}

bool GameObjectWithAnimatedSprite::IsFlippedX()
{
    const sf::Vector2f scale = GetScale();
	return scale.x < 0;
}

bool GameObjectWithAnimatedSprite::IsFlippedY()
{
    const sf::Vector2f scale = GetScale();
	return scale.y < 0;
}

void GameObjectWithAnimatedSprite::AddSpriteSheet(const char* filename)
{
    GameDataManager* manager = C_SysContext::Get<GameDataManager>();
    
    if (!manager->LoadSpritesheetDefFromFile(filename))
    {
	    LOG("Error loading spritesheet: " + std::string(filename))
        return;
    }
    m_spritesheet = manager->GetSpritesheetDef(filename);
}

void GameObjectWithAnimatedSprite::AddAnimation(int animationState, const char* animationName, int fps, bool repeating)
{
    AddAnimationFromSpriteSheetDef(animationState, m_spritesheet, animationName, fps, repeating);
}

void GameObjectWithAnimatedSprite::SetCurrentAnimation(int animationNumber)
{
    if (GetCurrentAnimation() == animationNumber)
    {
        return;
    }
    AnimatedSprite::SetCurrentAnimation(animationNumber);
}

void GameObjectWithAnimatedSprite::SetUIObject(bool isUIObject) {
    m_lisUIObject = isUIObject;
}
