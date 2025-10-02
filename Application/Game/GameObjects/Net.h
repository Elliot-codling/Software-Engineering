#ifndef _NET_H_
#define _NET_H_

#include "../../Core/Renderer/Sprite.h"

class ASCIIRenderer;



class Net : public Sprite
{
public:

	Net();
	~Net();

	void Initialise(Vector2& position);
	void Update();
	void Render(ASCIIRenderer* pRenderer);

private:

	bool m_bInitialised;

};

#endif
