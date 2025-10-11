#include "GameObjectWithAnimatedSprite.h"

#include <iostream>

void GameObjectWithAnimatedSprite::Initialise()
{
    
    for (int i = 0; i < 6; i++)
    {
        spriteRect = {0 + (i * 256), 0, 256, 256};
        m_Frames.push_back(spriteRect);
        m_Origins.push_back(origin);
    }
    m_AnimatedSprite.AddAnimation(0, "sprites/spritesheet_test.png", m_Frames, m_Origins, 10, true);

    m_AnimatedSprite.SetCurrentAnimation(0);
}

void GameObjectWithAnimatedSprite::Update()
{
    m_AnimatedSprite.Animate();
    m_AnimatedSprite.move({1, 0});
    m_AnimatedSprite.rotate(1.0f);
    
    if (m_AnimatedSprite.getScale().x > 3.0f)
    {
        scaleObject = false;
    }
    if (m_AnimatedSprite.getScale().x < 0.5f)
    {
        scaleObject = true;
    }
    
    if (scaleObject)
    {
        m_AnimatedSprite.scale(scaleFactor, scaleFactor);
    }
    else
    {
        m_AnimatedSprite.scale(2 - scaleFactor, 2 - scaleFactor);
    }
    
}

void GameObjectWithAnimatedSprite::GetPosition(float& px, float& py)
{
    px = this->m_AnimatedSprite.getPosition().x;
    py = this->m_AnimatedSprite.getPosition().y;
}

sf::Vector2f GameObjectWithAnimatedSprite::GetPosition()
{
    return this->m_AnimatedSprite.getPosition();
}

void GameObjectWithAnimatedSprite::SetPosition(float px, float py)
{
    this->m_AnimatedSprite.setPosition(px,py);
}

void GameObjectWithAnimatedSprite::SetPosition(sf::Vector2f ppos)
{
    this->m_AnimatedSprite.setPosition(ppos);
}
