#pragma once

#include "../../../Engine/Core/GameObject.h"
#include "../../../Engine/Renderer/AnimatedSprite.h"

class GameObjectWithAnimatedSprite : public GameObject, public AnimatedSprite
{
public:
    GameObjectWithAnimatedSprite() = default;
    virtual ~GameObjectWithAnimatedSprite() = default;

    // ### GameObject override functions ###
    void Initialise() override;
    void Update() override;
    
    // ### Transforms ###
    // --- Position ---
    void GetPosition(float& px, float& py) override;
    sf::Vector2f GetPosition() override;

    void SetPosition(float px, float py) override;
    void SetPosition(sf::Vector2f ppos) override;
    void IncrementPosition(sf::Vector2f ppos);
    // --- Rotation ---
    float GetAngle() const;
    void SetAngle(float angle);
    void IncrementAngle(float angle);
    // --- Scale ---
    sf::Vector2f GetScale() const;
    void IncrementScale(sf::Vector2f scale);
    void SetScale(sf::Vector2f scale);
    void SetScaleInPixels(sf::Vector2f scale);

    // Negative will flip sprite to the left, positive to the right
    void FlipX(bool flipSprite);
    void FlipY(bool flipSprite);
    bool IsFlippedX();
    bool IsFlippedY();

	// --- Animation functions ---
    void AddSpriteSheet(const char* filename);
    void AddAnimation(int animationState, const char* animationName, int fps, bool repeating);
    void SetCurrentAnimation(int animationNumber) override;

    void SetUIObject(bool isUIObject = false);

protected:
    // Animation setup
    sf::IntRect spriteRect;
    std::vector<sf::IntRect> m_Frames;
    
    sf::Vector2f origin = {0, 0};
    std::vector<sf::Vector2f> m_Origins;

    // SpriteSheet Setup
    SpritesheetDef* m_spritesheet = nullptr;

private:
    bool m_lisUIObject = false;
    
};
