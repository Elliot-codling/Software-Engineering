#include "ScrollableBackground.h"

#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Engine/System/Assets/AssetManager.h"
#include "../../../Engine/Renderer/WindowManager.h"

void ScrollableBackground::Initialise() {
    AddToRenderQueue();
}

void ScrollableBackground::Create(const char* fileName) {
    m_windowSize = C_SysContext::Get<WindowManager>()->GetWindow().getSize();

    sf::IntRect iBounds(0.f, 0.f, m_windowSize.x, m_windowSize.y);
    sf::Color halfOpacity = sf::Color(255.0f, 255.0f, 255.0f, 255.0f * 0.5f);

    Sprite::Initialise(fileName, halfOpacity, 1.0f);
    SetTexture(fileName, true);
    setPosition(iBounds.left, iBounds.top);
    setTextureRect(iBounds);

    m_offset = sf::Vector2i(0, 0);
}

void ScrollableBackground::Update() {
    // Scroll offset
    m_offset.x -= 1;
    m_offset.y -= 1;

    sf::IntRect rect(0, 0, m_windowSize.x, m_windowSize.y);

    // Apply texture
    int left = rect.left + m_offset.x;
    int top = rect.top + m_offset.y;
   
    setTextureRect(sf::IntRect(left, top, rect.width, rect.height));
}  