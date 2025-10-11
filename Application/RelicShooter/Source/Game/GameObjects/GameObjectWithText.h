#pragma once

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/UI/Text.h"

class GameObjectWithText : public GameObject
{
public:
	//-------CONSTRUCTORS/DESTRUCTORS-------------------------------------------
	GameObjectWithText();							//Zero Parameter Constructor
	~GameObjectWithText() override;					//Destructor

	//-------FUNCTIONS----------------------------------------------------------
public: 
	void GetPosition(float& px, float& py) override;	//Inherited From GameObject
	sf::Vector2f GetPosition() override;			//Inherited From GameObject
	void SetPosition(float px, float py) override;		//Inherited From GameObject
	void SetPosition(sf::Vector2f ppos) override;	//Inherited From GameObject

	void Initialise() override;						//Inherited From GameObject
	void Update() override;							//Inherited From GameObject

	//--------TEXT FUNCTIONS-----------------------------------------------------
	void SetDisplayText(std::string ptext);			
	void SetColour(sf::Color pcolour);
	void SetCharSize(int psize);
	void SetFontFile(std::string pfont);

	std::string GetDisplayText();
	sf::Color GetColour();
	int GetCharSize();
	std::string GetFontFile();
		 
protected:
	//--------MEMBER DATA---------------------------------------------------------
	Text		m_Text;		//Instance of the Engine's Text Class
	std::string m_Font;		//Store the Font File Data
	std::string m_String;	//Store the Text String
	sf::Color   m_Colour;	//Store the Colour
	int         m_Size;		//Store the Size
};

