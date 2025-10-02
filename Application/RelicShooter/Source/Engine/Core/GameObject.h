#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H
#include <SFML/System/Vector2.hpp>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialise() = 0;
	virtual void Update() = 0;
	virtual sf::Vector2f GetPosition() = 0;
	virtual void SetPosition(float px, float py) = 0;
	virtual void SetPosition(sf::Vector2f ppos) = 0;
	virtual void GetPosition(float& x, float & y) = 0;

};

#endif
