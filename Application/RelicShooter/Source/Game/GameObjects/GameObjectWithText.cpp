#include "GameObjectWithText.h"

//---------CONSTRUCTORS/DESTRUCTORS-------------------------------------------------------------

/**
 * \brief Constructor for this class.
 * Uses Initialiser Lists Constructors as standard
 */
GameObjectWithText::GameObjectWithText()
	: m_Text(),m_Font("fonts/8-BIT WONDER.TTF"),m_String("Hello World"), m_Colour(sf::Color::Red), m_Size(75)
{

}

/**
 * \brief Destructor for our Text Game Object
 * No dynamic memory is used in this class currently.
 */
GameObjectWithText::~GameObjectWithText()
{
}

//---------GAME OBJECT INTERFACE----------------------------------------------------------------

/**
 * \brief Get the Position as separate variables via References
 * \param  px - the current x position
 * \param  py - the current y position
 */
void GameObjectWithText::GetPosition(float& px, float& py)
{
	px = this->m_Text.getPosition().x;
	py = this->m_Text.getPosition().y;
}

/**
 * \brief Get the Position as a 2D Vector via Return
 * \return the current position as a 2D Vector
 */
sf::Vector2f GameObjectWithText::GetPosition()
{
	return this->m_Text.getPosition();
}

/**
 * \brief Create the Text Object and add it to the Renderer
 */
void GameObjectWithText::Initialise()
{
	//Use the Text class's Initialise function to create the SFML Text and add it to our Renderer.
	m_Text.Initialise(this->m_Font.c_str(),this->m_String.c_str(),this->m_Colour,this->m_Size);
}

/**
 * \brief Update the position the text is rendered at
 * \param px - the x position to move to
 * \param py - the y position to move to
 */
void GameObjectWithText::SetPosition(float px, float py)
{
	this->m_Text.setPosition(px,py);
}

/**
 * \brief Update the position the text is rendered at
 * \param ppos - the position to move to
 */
void GameObjectWithText::SetPosition(sf::Vector2f ppos)
{
	this->m_Text.setPosition(ppos);
}

/**
 * \brief Update the Text Object once per frame
 */
void GameObjectWithText::Update()
{
	//TODO:  Add code to update the Text Object automatically
	//Have a look at Text::Initialise as to what that code might look like!
}


//---------TEXT SPECIFIC FUNCTIONS-------------------------------------------------------------

/**
 * \brief  Set the Display Text
 * \param ptext - the Text to display
 */
void GameObjectWithText::SetDisplayText(std::string ptext)
{
	this->m_String = ptext;
}

/**
 * \brief Set the Display Colour
 * \param pcolour - Colour of the Text
 */
void GameObjectWithText::SetColour(sf::Color pcolour)
{
	this->m_Colour = pcolour;
}

/**
 * \brief Set the Character Size
 * \param psize - Size of the Text
 */
void GameObjectWithText::SetCharSize(int psize)
{
	this->m_Size = psize;
}

/**
 * \brief Set the Font File Used
 * \param pfont - The Path and File Name of the Font 
 */
void GameObjectWithText::SetFontFile(std::string pfont)
{
	this->m_Font = pfont;
}

/**
 * \brief Get the Display Text Currently Stored
 * \return std::string containing the Text
 */
std::string GameObjectWithText::GetDisplayText()
{
	return this->m_String;
}

/**
 * \brief Get the Current Colour
 * \return sf::Color containing the colour
 */
sf::Color GameObjectWithText::GetColour()
{
	return this->m_Colour;
}

/**
 * \brief Get the Current Character Size
 * \return sf::Character Size
 */
int GameObjectWithText::GetCharSize()
{
	return this->m_Size;
}

/**
 * \brief Get the Font File used
 * \return the Path and File Name as a std::string
 */
std::string GameObjectWithText::GetFontFile()
{
	return this->m_Font;
}