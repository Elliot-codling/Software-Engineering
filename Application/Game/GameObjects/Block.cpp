#include "Block.h"

int BlockSprite[] =
{
	BACKGROUND_WHITE, BACKGROUND_WHITE, BACKGROUND_WHITE
};

Block::Block()
{
}

Block::~Block()
{

}

void Block::Initialise()
{
	Sprite::Initialise(BlockSprite, Vector2(3, 1));
}

void Block::Update()
{

}

void Block::Render(ASCIIRenderer* pRenderer)
{
	Sprite::Render(pRenderer);
}

