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

void Text::Initialise(const char* pfilename, const char* ptext)
{
	const auto pAssetManager = C_SysContext::Get<AssetManager>();
	setFont(*pAssetManager->GetFont(pfilename));

	setString(ptext); //Set the Text
	setCharacterSize(75); // in pixels, not points!
	setFillColor(sf::Color::Red);
	//m_Text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	C_SysContext::Get<RenderManager>()->AddRenderObject(this);
	m_Initialised = true;
}
