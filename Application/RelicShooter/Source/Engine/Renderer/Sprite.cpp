#include "Sprite.h"
#include "../System/Assets/AssetManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "RenderManager.h"
#include "../../Game/DebugHandler.hpp"

Sprite::Sprite()
	:m_bInitialised(false)
{
}

Sprite::~Sprite()
{
	if (m_isUIObject) {
	    C_SysContext::Get<RenderManager>()->RemoveUIRenderObject(this);
	}
	else {
	    C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
	}
}

void Sprite::Initialise(const char* filename,sf::Color pcolour,float pscale, bool isUIObject)
{
	SetTexture(filename);
	setColor(pcolour);
	setScale(sf::Vector2f(pscale,pscale));
	m_bInitialised = true;

	m_isUIObject = isUIObject;
}

void Sprite::AddToRenderQueue() {
	if (m_isUIObject) {
	    C_SysContext::Get<RenderManager>()->AddUIRenderObject(this);
	}
	else {
	    C_SysContext::Get<RenderManager>()->AddRenderObject(this);
	}
}

void Sprite::SetTexture(const char* fileName, const bool repeat) {
	auto pAssetManager = C_SysContext::Get<AssetManager>();
	sf::Texture& texture = pAssetManager->GetTexture(fileName);
	texture.setRepeated(repeat);
	setTexture(texture);
}
