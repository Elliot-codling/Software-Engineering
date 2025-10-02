#ifndef _PlayerShip_H_
#define _PlayerShip_H_

#include "../../Core/Renderer/Sprite.h"

class ASCIIRenderer;

extern const int SCREEN_WIDTH;

class PlayerShip : public Sprite
{
public:

	PlayerShip();
	~PlayerShip();

	void Initialise(Vector2& position, int leftKey, int rightKey);
	void Update();
	void Render(ASCIIRenderer* pRenderer);
	
private:

	void MoveLeft();
	void MoveRight();

	int m_LeftKey;
	int m_RightKey;

	bool LeftKeyPressed();
	bool RightKeyPressed();

	bool m_bInitialised;

};

#endif
