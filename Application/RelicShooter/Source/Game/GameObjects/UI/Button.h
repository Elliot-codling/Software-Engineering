#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include "../../../Engine/Core/GameObject.h"
#include "../../../Engine/Renderer/Sprite.h"

class GameObjectWithText;
class GameState;

const sf::Color IDLE_COLOUR = sf::Color::White;
const sf::Color HOVERED_COLOUR = sf::Color(200, 200, 200);
const sf::Color PRESSED_COLOUR = sf::Color(100, 100, 100);

class Button : public GameObject, Sprite {
public:
	enum ButtonState {
	    IDLE,
		HOVERED,
		PRESSED
	};

public:
	Button();
	Button(const char* spriteFileName, const sf::Vector2f& pos, const float scale = 1.f);
	~Button() override;

public:

	void Initialise() override;
	void Update() override;

	void SetSpriteFile(const char* psprite);
	void SetHoveredSpriteFile(const char* psprite);
	void SetClickedSpriteFile(const char* psprite);
	void SetScale(const float pscale);

	void CreateButton(bool isUIObject = false);

	/* Text Functions */
	void CreateAndSetButtonText(sf::Vector2f pos, const char* text, sf::Color colour, int size, std::string fontFile);
	GameObjectWithText* GetTextObject() { return m_textObject; }

	/* Rect */
	void CalculateRect();
	sf::IntRect& GetSpriteRect() { return m_spriteRect; }

	/* Button Events */
	void AddHoverEventFunction(std::function<void()> hoverFunction);
	void AddUnhoverEventFunction(std::function<void()> unhoverFunction);
	void AddClickEventFunction(std::function<void()> clickFunction);
	void AddClickReleasedEventFunction(std::function<void()> clickReleaseFunction);

	void CheckIfHovered(const sf::Vector2i& mousePos);
	void EventHovered();
	void EventUnhovered();
	void EventClicked();
	void EventClickReleased();

    ButtonState GetButtonState() const { return m_currentButtonState; }

	void GetPosition(float& px, float& py) override;
	sf::Vector2f GetPosition() override;
	void SetPosition(float px, float py) override;
	void SetPosition(sf::Vector2f ppos) override;
protected:
	/* Sprite */
	const char* m_spriteImages[3];
	float m_scale;
	sf::Vector2f m_spritePosition;

	/* Button */
	sf::IntRect m_spriteRect;
	ButtonState m_currentButtonState;

	/* Text */
	GameObjectWithText* m_textObject;
	const char* m_text;

private:
	std::function<void()> m_onHoverFunction;
	std::function<void()> m_onUnhoverFunction;
	std::function<void()> m_onClickFunction;
	std::function<void()> m_onClickReleaseFunction;

	bool m_wasClickPressed = false;

	bool m_isUIObject = false;
};

#endif