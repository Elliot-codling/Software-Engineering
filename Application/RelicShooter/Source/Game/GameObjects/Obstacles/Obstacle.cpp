#include "Obstacle.h"

//---------CONSTRUCTORS/DESTRUCTORS-------------------------------------------------------------

Obstacle::Obstacle()
	//: m_Sprite(), m_SpriteImage("sprites/error/error_image.png"), m_Colour(sf::Color::White), m_Scale(1.f)
{

}

Obstacle::Obstacle(const sf::Vector2f& pos, const float scale, sf::Color colour)
    //: m_Colour(colour),
    //m_Scale(scale)
{
	// m_SpriteImage keeps having a bug
	// No idea what it is as of now, something about calling without appropriate operator or conversion function
	// And I keep getting ignored in the call so I'll just ask tomorrow in person

	
	int randomNumber = rand() % 4;

	switch(randomNumber)
	{
		case(0):
			m_SpriteImage = "sprites/obstacles/spr_barrel_0.png";
			break;
		case(1):
			m_SpriteImage = "sprites/obstacles/spr_barrelDucan_0.png";
			break;
		case(2):
			m_SpriteImage = "sprites/obstacles/spr_barrelDucan_1.png";
			break;
		case(3):
			m_SpriteImage = "sprites/obstacles/spr_barrelDucan_1.png";
			break;
		default:
			m_SpriteImage = "sprites/error/error_image.png";
			break;
	}
	
    SetPosition(pos);
}

//---------GAME OBJECT INTERFACE----------------------------------------------------------------


void Obstacle::Initialise()
{
	//Use the Sprite class's Initialise function to create the SFML Sprite and add it to our Renderer.
	m_Sprite.AddToRenderQueue();
}

void Obstacle::Update()
{
	//TODO:  Add code to update the Sprite Object automatically
	//Have a look at Sprite::Initialise as to what that code might look like!
}

sf::FloatRect Obstacle::getGlobalBounds() const
{
	return m_Sprite.getGlobalBounds();
}