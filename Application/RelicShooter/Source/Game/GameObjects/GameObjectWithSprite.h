#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/Sprite.h"

class GameObjectWithSprite : public GameObject
{
public:
	
	GameObjectWithSprite() = default;							//Zero Parameter Constructor
	~GameObjectWithSprite() override = default;					//Destructor

	void Initialise() override;
	void Update() override;

	// ### Transforms ###
	// Position
	void GetPosition(float& px, float& py) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;

	void incrementPosition(sf::Vector2f position);
	// Scale
	sf::Vector2f GetScale();
	void SetScale(sf::Vector2f scale);
	void incrementScale(sf::Vector2f scale);

	// Rotation
	float GetRotation();
	void SetRotation(float rotation);
	void incrementRotation(float rotation);

	// ### Colour ###
	sf::Color GetColor();
	void SetColor(sf::Color color);


	// ### Texture ###
	void ReplaceTexture(const char* directory);



private:
	sf::Texture* m_texture = new sf::Texture;
	Sprite m_Sprite;
	float scaleFactor = 1.2f;
};

