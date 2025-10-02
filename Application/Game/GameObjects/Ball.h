#ifndef _BALL_H_
#define _BALL_H_

#include "../../Core/Maths/Vector2.h"
#include "../../Core/Renderer/Sprite.h"

class ASCIIRenderer;

class Ball : public Sprite
{
public:

	Ball();
	~Ball();

	void Initialise(Vector2& courtSize);
	void Update();
	void Render(ASCIIRenderer* pRenderer);

	void BounceOffPaddle();

private:

	bool CollideWithVerticalWalls();
	bool CollideWithHorizontalWalls();

	Vector2 m_MovementDirecteion;
	Vector2 m_PreviousPosition;

	Vector2 m_CourtSize;

};

#endif