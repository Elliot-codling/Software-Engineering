#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Player;
class RayCastLine
{
public:
	RayCastLine() = default;
	~RayCastLine() = default;

public:
	void Initialise();
	void Update(Player* player);

	// --- Transform
	// Position
	void SetPosition(sf::Vector2f position);
	void SetLength(float length);

	// --- Render ---
	void SetVisibility(bool visible);

private:
	// Window context
	size_t m_windowWidth;
	size_t m_windowHeight;
	float m_aspectRatio;

	// Rectangle
	sf::RectangleShape m_rectangle;
	float m_thickness = 2.5f;
	const sf::Color m_lineColor = { 255, 0, 0 };

};

