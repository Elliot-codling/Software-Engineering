#include "PointsUIComponent.h"

void PointsUIComponent::Initialise() {
    m_pointsText.Initialise("fonts/BoldPixels.ttf", "0", sf::Color::White, 75, true);
    m_pointsText.setOrigin(0, 0);
    m_pointsText.setPosition(sf::Vector2f(1920 - m_pointsText.getGlobalBounds().width + m_pointsText.getLocalBounds().left - 25.0f, 1080.0f - m_pointsText.getGlobalBounds().height - m_pointsText.getLocalBounds().top - 25.0f));
    //m_pointsText.setPosition(sf::Vector2f(0 , 0 - m_pointsText.getLocalBounds().top));
}

void PointsUIComponent::Update(int points) {
    if (m_pointsLastUpdate == points) {
        return;
    }

    UpdatePoints(points);
}

void PointsUIComponent::UpdatePoints(int points) {
    m_pointsLastUpdate = points;
    m_pointsText.setString(std::to_string(points));
    m_pointsText.setPosition(sf::Vector2f(1920 - m_pointsText.getGlobalBounds().width + m_pointsText.getLocalBounds().left - 25.0f, 1080.0f - m_pointsText.getGlobalBounds().height - m_pointsText.getLocalBounds().top - 25.0f));
}
