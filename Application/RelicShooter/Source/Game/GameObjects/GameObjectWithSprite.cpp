#include "GameObjectWithSprite.h"

#include "../../Engine/Renderer/FrameTimer.h"


void GameObjectWithSprite::Initialise()
{
	m_Sprite.Initialise("");
}

void GameObjectWithSprite::Update()
{
	/*
	// EXPERIMENTAL
	const float deltaTime = 1.f / 60.f;
	const float velocity = 10.0f;
	
	m_Sprite.setPosition(GetPosition().x + (velocity * deltaTime), GetPosition().y + (velocity * deltaTime));
	m_Sprite.rotate(10 * deltaTime);

	if (m_Sprite.getScale().x < 1 || m_Sprite.getScale().y < 1)
	{
		scaleFactor *= -1;
	}
	if (m_Sprite.getScale().x > 3 || m_Sprite.getScale().y > 3)
	{
		scaleFactor *= -1;
	}

	m_Sprite.setScale(m_Sprite.getScale().x + (scaleFactor * deltaTime), m_Sprite.getScale().y + (scaleFactor * deltaTime));
	*/
	
}

void GameObjectWithSprite::GetPosition(float& px, float& py)
{
	px = m_Sprite.getPosition().x;
	py = m_Sprite.getPosition().y;
	
}

sf::Vector2f GameObjectWithSprite::GetPosition()
{
	return m_Sprite.getPosition();
}

void GameObjectWithSprite::SetPosition(float px, float py)
{
	m_Sprite.setPosition(px, py);
}

void GameObjectWithSprite::SetPosition(sf::Vector2f ppos)
{
	m_Sprite.setPosition(ppos);
}

void GameObjectWithSprite::incrementPosition(sf::Vector2f position)
{
	m_Sprite.move(position);
}

sf::Vector2f GameObjectWithSprite::GetScale()
{
	return m_Sprite.getScale();
}

void GameObjectWithSprite::SetScale(sf::Vector2f scale)
{
	m_Sprite.setScale(scale);
}

void GameObjectWithSprite::incrementScale(sf::Vector2f scale)
{
	m_Sprite.scale(scale);
}

float GameObjectWithSprite::GetRotation()
{
	return m_Sprite.getRotation();
}

void GameObjectWithSprite::SetRotation(float rotation)
{
	m_Sprite.setRotation(rotation);
}

void GameObjectWithSprite::incrementRotation(float rotation)
{
	m_Sprite.rotate(rotation);
}

sf::Color GameObjectWithSprite::GetColor()
{
	return m_Sprite.getColor();
}

void GameObjectWithSprite::SetColor(sf::Color color)
{
	m_Sprite.setColor(color);
}

void GameObjectWithSprite::ReplaceTexture(const char* directory)
{
	if (!m_texture->loadFromFile(directory))
	{
		return;
	}
	m_Sprite.setTexture(*m_texture, true);
}
