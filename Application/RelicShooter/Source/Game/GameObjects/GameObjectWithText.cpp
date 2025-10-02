#include "GameObjectWithText.h"

void GameObjectWithText::Initialise()
{
	m_Text.Initialise("fonts/8-BIT WONDER.TTF", "Hello World");
	
}

void GameObjectWithText::GetPosition(float& x, float& y)
{
	x = m_Text.getPosition().x;
	y = m_Text.getPosition().y;
}

sf::Vector2f GameObjectWithText::GetPosition()
{
	return m_Text.getPosition();
}

void GameObjectWithText::SetPosition(float px, float py)
{
	m_Text.setPosition(px, py);
}

void GameObjectWithText::SetPosition(sf::Vector2f ppos)
{
	m_Text.setPosition(ppos);
}

void GameObjectWithText::SetFont(const char* filename)
{
	
	font.loadFromFile(filename);
	m_Text.setFont(font);
}

void GameObjectWithText::SetColor(sf::Color textColor)
{
	m_Text.setFillColor(textColor);
}

void GameObjectWithText::SetFontSize(uint8_t fontSize)
{
	m_Text.setCharacterSize(fontSize);
}

void GameObjectWithText::SetText(const char* text)
{
	m_Text.setString(text);
}

