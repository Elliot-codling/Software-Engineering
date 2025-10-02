#include "Net.h"
#include "../../Core/Renderer/ASCIIRenderer.h"

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

int NetSprite[] =
{
	BACKGROUND_GREY, BACKGROUND_GREY, BACKGROUND_BLACK, BACKGROUND_BLACK, BACKGROUND_GREY, BACKGROUND_GREY, BACKGROUND_BLACK, BACKGROUND_BLACK, BACKGROUND_GREY, BACKGROUND_GREY, BACKGROUND_BLACK, BACKGROUND_BLACK,
	BACKGROUND_GREY, BACKGROUND_GREY, BACKGROUND_BLACK, BACKGROUND_BLACK, BACKGROUND_GREY, BACKGROUND_GREY, BACKGROUND_BLACK, BACKGROUND_BLACK, BACKGROUND_GREY, BACKGROUND_GREY, BACKGROUND_BLACK, BACKGROUND_BLACK,
	BACKGROUND_GREY, BACKGROUND_GREY
};

Net::Net()
:m_bInitialised(false)
{

}

Net::~Net()
{

}

void Net::Initialise(Vector2& position)
{
	Sprite::Initialise(NetSprite, Vector2(1, 26));
	SetPosition(position);

	m_bInitialised = true;
}

void Net::Update()
{

}

void Net::Render(ASCIIRenderer* pRenderer)
{
	if (!m_bInitialised)
		return;

	Sprite::Render(pRenderer);
}
