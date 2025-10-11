#pragma once

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/Sprite.h"

class GameObjectWithSprite : public GameObject
{
public:
	//-------CONSTRUCTORS/DESTRUCTORS-------------------------------------------
	GameObjectWithSprite();							//Zero Parameter Constructor
	~GameObjectWithSprite() override;					//Destructor

	//-------FUNCTIONS----------------------------------------------------------
public: 
	void GetPosition(float& px, float& py) override;	//Inherited From GameObject
	sf::Vector2f GetPosition() override;			//Inherited From GameObject
	void SetPosition(float px, float py) override;		//Inherited From GameObject
	void SetPosition(sf::Vector2f ppos) override;	//Inherited From GameObject

	void Initialise() override;						//Inherited From GameObject
	void Update() override;							//Inherited From GameObject

	//--------TEXT FUNCTIONS-----------------------------------------------------

	void SetColour(sf::Color pcolour);
	void SetSpriteFile(std::string psprite);
	void SetScale(float pscale);

	sf::Color GetColour();
	float GetScale();
	std::string GetSpriteFile();
		 
protected:
	//--------MEMBER DATA---------------------------------------------------------
	Sprite		m_Sprite;		//Instance of the Engine's Sprite Class
	std::string m_SpriteImage;	//Store the Sprite Image Data
	sf::Color   m_Colour;		//Store the Colour
	float       m_Scale;		//Store the Scale

};

