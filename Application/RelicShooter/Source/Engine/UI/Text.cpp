#include "Text.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/Assets/AssetManager.h"
#include "../../Engine/Renderer/RenderManager.h"

Text::Text()
	:m_Initialised(false)
{

}

Text::~Text()
{
	C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
}

void Text::Initialise(const char* filename, const char* text, sf::Color pcolour, int psize, bool isUIObject)
{
	auto pAssetManager = C_SysContext::Get<AssetManager>();
	setFont(*pAssetManager->GetFont(filename));

	setString(text); //Set the Text
	setCharacterSize(psize); // in pixels, not points!
	setFillColor(pcolour);
	//m_Text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	/* Choose whether to add it to the world or to the UI */
	if (isUIObject) {
	    C_SysContext::Get<RenderManager>()->AddUIRenderObject(this);
	}
	else {
	    C_SysContext::Get<RenderManager>()->AddRenderObject(this);
	}
	m_Initialised = true;
}
