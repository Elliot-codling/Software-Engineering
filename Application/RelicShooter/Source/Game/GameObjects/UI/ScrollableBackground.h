#ifndef SCROLLABLEBACKGROUND_H
#define SCROLLABLEBACKGROUND_H

#include "../../../Engine/Core/GameObject.h"
#include "../../../Engine/Renderer/Sprite.h"

class ScrollableBackground : public GameObject, Sprite {
public:
    ScrollableBackground() = default;
    ~ScrollableBackground() override = default;

public:
    void Initialise() override;
    void Update() override;

    void GetPosition(float& px, float& py) override {}
    sf::Vector2f GetPosition() override { return {0, 0}; }
    void SetPosition(float px, float py) override {}
    void SetPosition(sf::Vector2f ppos) override {}

    void Create(const char* fileName);

private:
    const char* m_spriteFileName;
    sf::Texture* m_texture;

    sf::Vector2u m_windowSize;

    sf::Vector2i m_offset;
};

#endif