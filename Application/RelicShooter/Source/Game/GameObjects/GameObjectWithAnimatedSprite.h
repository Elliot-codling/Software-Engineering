#pragma once
#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/AnimatedSprite.h"

class GameObjectWithAnimatedSprite : public GameObject
{
public:
    GameObjectWithAnimatedSprite() = default;
    ~GameObjectWithAnimatedSprite() = default;

    void Initialise() override;
    void Update() override;
    void GetPosition(float& px, float& py) override;
    sf::Vector2f GetPosition();
    void SetPosition(float px, float py) override;
    void SetPosition(sf::Vector2f ppos) override;


private:
    AnimatedSprite m_AnimatedSprite;

    sf::IntRect spriteRect;
    std::vector<sf::IntRect> m_Frames;
    
    sf::Vector2f origin = {0, 0};
    std::vector<sf::Vector2f> m_Origins;

    bool scaleObject = true;
    float scaleFactor = 1.05f;
    
    
};
