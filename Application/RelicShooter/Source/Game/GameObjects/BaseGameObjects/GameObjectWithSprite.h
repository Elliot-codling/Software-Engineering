#pragma once

#include "../../../Engine/Core/GameObject.h"
#include "../../../Engine/Renderer/Sprite.h"

class GameObjectWithSprite : public GameObject
{
public:
	//-------CONSTRUCTORS/DESTRUCTORS-------------------------------------------
	GameObjectWithSprite();							//Zero Parameter Constructor
	GameObjectWithSprite(const char* spriteFileName, const sf::Vector2f& pos, const float scale = 1, sf::Color colour = sf::Color::White);
	~GameObjectWithSprite() override;					//Destructor

	//-------FUNCTIONS----------------------------------------------------------
public: 
	void GetPosition(float& px, float& py) override;	//Inherited From GameObject
	sf::Vector2f GetPosition() override;			//Inherited From GameObject
	void SetPosition(float px, float py) override;		//Inherited From GameObject
	void SetPosition(sf::Vector2f ppos) override;	//Inherited From GameObject

	void Initialise() override;						//Inherited From GameObject
	void Update() override;							//Inherited From GameObject

	void CreateSprite();

	//--------TEXT FUNCTIONS-----------------------------------------------------

	void SetColour(sf::Color pcolour);
	void SetSpriteFile(const char* psprite);
	void SetScale(float pscale);
	void SetScaleInPixels(sf::Vector2i scale);

	void SetSprite(const char* fileName);

	sf::Color GetColour();
	float GetScale();
	std::string GetSpriteFile();
		 
protected:
	//--------MEMBER DATA---------------------------------------------------------
	Sprite		m_Sprite;		//Instance of the Engine's Sprite Class
	const char* m_SpriteImage;	//Store the Sprite Image Data
	sf::Color   m_Colour;		//Store the Colour
	float       m_Scale;		//Store the Scale

};

