#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/UI/Text.h"

class GameObjectWithText : public GameObject
{
public:
	GameObjectWithText() = default;
	~GameObjectWithText() override = default;

public:
	void Initialise() override;
	void Update() override {};

	void GetPosition(float& x, float& y) override;
	sf::Vector2f GetPosition() override;
	

	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;


	void SetFont(const char* filename);
	void SetColor(sf::Color textColor);
	void SetFontSize(uint8_t fontSize);
	void SetText(const char* text);

private:
	Text m_Text;
	sf::Font font;
};

