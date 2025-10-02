#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../../Core/Renderer/Sprite.h"
#include "../../Core/Renderer/ConsoleColours.h"



class Block : public Sprite
{
public:
	Block();
	~Block();

	void Initialise();
	void Update();
	void Render(ASCIIRenderer* pRenderer);

private:

};

#endif