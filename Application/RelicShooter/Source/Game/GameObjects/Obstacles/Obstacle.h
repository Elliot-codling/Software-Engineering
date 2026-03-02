#pragma once
#include "../BaseGameObjects/GameObjectWithSprite.h"

class Obstacle :
	public GameObjectWithSprite
{
public:
    //-------CONSTRUCTORS/DESTRUCTORS-------------------------------------------
    Obstacle();
    Obstacle(const sf::Vector2f& pos, const float scale = 1, sf::Color colour = sf::Color::White);
    ~Obstacle() override = default;

	void Initialise() override;						//Inherited From GameObjectWithSprite
	void Update() override;							//Inherited From GameObjectWithSprite

    //-------FUNCTIONS----------------------------------------------------------
	//void GetPosition(float& px, float& py);	//Inherited From GameObjectWithSprite
	//sf::Vector2f GetPosition();			//Inherited From GameObjectWithSprite
	//void SetPosition(float px, float py);		//Inherited From GameObjectWithSprite
	//void SetPosition(sf::Vector2f ppos);	//Inherited From GameObjectWithSprite


    sf::FloatRect getGlobalBounds() const;

protected:
    //--------MEMBER DATA---------------------------------------------------------
    //Sprite		m_Sprite;		//Instance of the Engine's Sprite Class
    //std::string m_SpriteImage;	//Store the Sprite Image Data
    //sf::Color   m_Colour;		//Store the Colour
    //float       m_Scale;		//Store the Scale

};