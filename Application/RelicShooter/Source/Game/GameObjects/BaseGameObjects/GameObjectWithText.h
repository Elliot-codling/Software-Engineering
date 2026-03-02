#pragma once
class GameObject;

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include "../../../Engine/UI/Text.h"
#include "../../../Engine/Core/GameObject.h"

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

	sf::FloatRect GetLocalBounds() { return m_Text.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() { return m_Text.getGlobalBounds(); }

	void Initialise() override;						//Inherited From GameObject
	void Update() override;							//Inherited From GameObject

	GameObject* GetGameObject() { return this; }

	//--------TEXT FUNCTIONS-----------------------------------------------------
	void SetDisplayText(std::string ptext);			
	void SetColour(sf::Color pcolour);
	void SetCharSize(int psize);
	void SetFontFile(std::string pfont);
	void SetCharSpacing(float spacing);

	std::string GetDisplayText();
	sf::Color GetColour();
	int GetCharSize();
	std::string GetFontFile();

	void SetUIComponent(bool isUIObject) { m_isUIObject = isUIObject; }
		 
protected:
	//--------MEMBER DATA---------------------------------------------------------
	Text		m_Text;		//Instance of the Engine's Text Class
	std::string m_Font;		//Store the Font File Data
	std::string m_String;	//Store the Text String
	sf::Color   m_Colour;	//Store the Colour
	int         m_Size;		//Store the Size

	bool m_isUIObject = false;
};

