#include "GameObjectWithSprite.h"

//---------CONSTRUCTORS/DESTRUCTORS-------------------------------------------------------------

/**
 * \brief Constructor for this class.
 * Uses Initialiser Lists Constructors as standard
 */
GameObjectWithSprite::GameObjectWithSprite()
	: m_Sprite(),m_SpriteImage("sprites/spr_hud_face_raff_0.png"),m_Colour(sf::Color::White), m_Scale(1.0f)
{

}

/**
 * \brief Destructor for our Sprite Game Object
 * No dynamic memory is used in this class currently.
 */
GameObjectWithSprite::~GameObjectWithSprite()
{

}

//---------GAME OBJECT INTERFACE----------------------------------------------------------------

/**
 * \brief Get the Position as separate variables via References
 * \param  px - the current x position
 * \param  py - the current y position
 */
void GameObjectWithSprite::GetPosition(float& px, float& py)
{
	px = this->m_Sprite.getPosition().x;
	py = this->m_Sprite.getPosition().y;
}

/**
 * \brief Get the Position as a 2D Vector via Return
 * \return the current position as a 2D Vector
 */
sf::Vector2f GameObjectWithSprite::GetPosition()
{
	return this->m_Sprite.getPosition();
}

/**
 * \brief Create the Sprite Object and add it to the Renderer
 */
void GameObjectWithSprite::Initialise()
{
	//Use the Sprite class's Initialise function to create the SFML Sprite and add it to our Renderer.
	m_Sprite.Initialise(this->m_SpriteImage.c_str(),this->m_Colour,this->m_Scale);
}

/**
 * \brief Update the position the Sprite is rendered at
 * \param px - the x position to move to
 * \param py - the y position to move to
 */
void GameObjectWithSprite::SetPosition(float px, float py)
{
	this->m_Sprite.setPosition(px,py);
}

/**
 * \brief Update the position the Sprite is rendered at
 * \param ppos - the position to move to
 */
void GameObjectWithSprite::SetPosition(sf::Vector2f ppos)
{
	this->m_Sprite.setPosition(ppos);
}

/**
 * \brief Update the Sprite Object once per frame
 */
void GameObjectWithSprite::Update()
{
	//TODO:  Add code to update the Sprite Object automatically
	//Have a look at Sprite::Initialise as to what that code might look like!
}


//---------Sprite SPECIFIC FUNCTIONS-------------------------------------------------------------

/**
 * \brief  Set the Display Sprite Image Path
 * \param pSprite - the Sprite to display
 */
void GameObjectWithSprite::SetSpriteFile(std::string pSprite)
{
	this->m_SpriteImage = pSprite;
}

/**
 * \brief Set the Display Colour
 * \param pcolour - Colour of the Sprite
 */
void GameObjectWithSprite::SetColour(sf::Color pcolour)
{
	this->m_Colour = pcolour;
}

/**
 * \brief Set the Character Size
 * \param psize - Size of the Sprite
 */
void GameObjectWithSprite::SetScale(float psize)
{
	this->m_Scale = psize;
}


/**
 * \brief Get the Display Sprite Currently Stored
 * \return std::string containing the Sprite
 */
std::string GameObjectWithSprite::GetSpriteFile()
{
	return this->m_SpriteImage;
}

/**
 * \brief Get the Current Colour
 * \return sf::Color containing the colour
 */
sf::Color GameObjectWithSprite::GetColour()
{
	return this->m_Colour;
}

/**
 * \brief Get the Current Character Scale
 * \return sf::Character Size
 */
float GameObjectWithSprite::GetScale()
{
	return this->m_Scale;
}