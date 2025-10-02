#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "../../Core/Renderer/Sprite.h"

class ASCIIRenderer;

const int MISSILE_SPEED = 2;

class Missile : public Sprite
{
public:

	Missile();
	~Missile();

	void Initialise(Vector2& position, Vector2& velocity);
	void Update();
	void Render(ASCIIRenderer* pRenderer);
	void Explode();

	void SetActive(bool active = true) { m_Active = active; };
	bool Active() { return m_Active; }

private:

	Vector2 m_Velocity;

	bool m_bInitialised;
	bool m_Active;

};

#endif
