#include "Button.h"

#include "../../../Engine/Renderer/FrameTimer.h"
#include "../../../Engine/Renderer/WindowManager.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../BaseGameObjects/GameObjectWithText.h"

Button::Button() : m_spriteImages{ "sprites/error/error_image.png", nullptr, nullptr }, m_scale(0.25f)
{
}

Button::Button(const char* spriteFileName, const sf::Vector2f& pos, const float scale)
    : m_spriteImages{spriteFileName, nullptr, nullptr},
      m_scale(scale),
      m_spritePosition(pos),
      m_textObject(nullptr)
{
    SetPosition(m_spritePosition);
}

Button::~Button() {
    delete m_textObject;
}

void Button::CreateButton(bool isUIObject) {
    m_isUIObject = isUIObject;
    Sprite::Initialise(m_spriteImages[0], sf::Color::White, m_scale, m_isUIObject);
    CalculateRect();
}

void Button::Initialise() {
    AddToRenderQueue();
    if (m_textObject != nullptr) {
        m_textObject->Initialise();
    }
}

void Button::Update() {
    /* Get mouse position relative to window and output */
    const sf::Window& window = C_SysContext::Get<WindowManager>()->GetWindow();
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    /* Hover check */
    CheckIfHovered(mousePos);

    /* Mouse click logic */
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_wasClickPressed) { // Pressed
        m_wasClickPressed = true;

        /* Clicked and hovered */
        if (m_currentButtonState == HOVERED) {
            EventClicked();
        }
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_wasClickPressed) { // Released
        EventClickReleased();
    }
}

void Button::CalculateRect() {
    sf::IntRect rect = getTextureRect();
    /* this will lose some accuracy due to the static cast to int losing the float values  */
    m_spriteRect = {
        rect.left, rect.top,
        static_cast<int>(rect.width * m_scale), static_cast<int>(rect.height * m_scale)
    };
}

void Button::CheckIfHovered(const sf::Vector2i& mousePos) {
    if (m_currentButtonState == PRESSED) {
        return;
    }

    if (getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
    {
        EventHovered();
        return;
    }
    EventUnhovered();
}


void Button::AddClickEventFunction(std::function<void()> clickFunction) {
    m_onClickFunction = clickFunction;
}

void Button::EventHovered() {
    if (m_spriteImages[HOVERED] != nullptr) {
        SetTexture(m_spriteImages[HOVERED]);
    }
    else {
        setColor(HOVERED_COLOUR);
    }
    m_currentButtonState = HOVERED;

    /* Do Hover Function If Set */
    if (m_onHoverFunction) {
        m_onHoverFunction();
    }
}

void Button::EventUnhovered() {
    m_currentButtonState = IDLE;
    SetTexture(m_spriteImages[IDLE]);
    setColor(IDLE_COLOUR);

    /* Do Unhover Function If Set */
    if (m_onUnhoverFunction) {
        m_onUnhoverFunction();
    }
}

void Button::EventClicked() {
    /* set sprite image if is set */
    if (m_spriteImages[PRESSED] != nullptr) {
        SetTexture(m_spriteImages[PRESSED]);
    }
    else {
        setColor(PRESSED_COLOUR);
    }
    m_currentButtonState = PRESSED;

    /* Do Click Function If Set */
    if (m_onClickFunction) {
		m_onClickFunction();
    }
}

void Button::EventClickReleased() {
    /* set sprite image if is set */
    if (m_spriteImages[IDLE] != nullptr) {
        SetTexture(m_spriteImages[IDLE]);
    }
    else {
        setColor(IDLE_COLOUR);
    }
    m_currentButtonState = IDLE;
    m_wasClickPressed = false;

    /* Do Click Release Function If Set */
    if (m_onClickReleaseFunction) {
        m_onClickReleaseFunction();
    }
}


void Button::GetPosition(float& px, float& py) {
	px = getPosition().x;
	py = getPosition().y;
}
sf::Vector2f Button::GetPosition() {
	return getPosition();
}

void Button::SetPosition(float px, float py) {
	setPosition(px, py);
    m_spritePosition = sf::Vector2f(px, py);
    CalculateRect();
}
void Button::SetPosition(sf::Vector2f ppos) {
	setPosition(ppos);
    m_spritePosition = ppos;
    CalculateRect();
}

void Button::SetSpriteFile(const char* pSprite) {
	m_spriteImages[0]= pSprite;
}

void Button::SetHoveredSpriteFile(const char* psprite) {
    m_spriteImages[HOVERED] = psprite;
}

void Button::SetClickedSpriteFile(const char* psprite) {
    m_spriteImages[PRESSED] = psprite;
}

void Button::SetScale(const float psize) {
    m_scale = psize;
}

void Button::CreateAndSetButtonText(sf::Vector2f pos, const char* text, sf::Color colour, int size, std::string fontFile) {
    m_textObject = new GameObjectWithText();
    m_textObject->SetFontFile(fontFile);
    m_textObject->SetCharSize(size);
    m_textObject->SetColour(colour);
    m_textObject->SetDisplayText(text);
    m_textObject->SetPosition(pos);
    m_textObject->SetUIComponent(m_isUIObject);
}