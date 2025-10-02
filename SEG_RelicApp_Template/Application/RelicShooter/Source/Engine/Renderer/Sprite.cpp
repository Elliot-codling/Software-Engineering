#include "Sprite.h"
#include "../System/Assets/AssetManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "RenderManager.h"

Sprite::Sprite()
	:m_bInitialised(false)
{
}

Sprite::~Sprite()
{
	C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
}

void Sprite::Initialise(const char* filename)
{
	auto* pAssetManager = C_SysContext::Get<AssetManager>();
	setTexture(pAssetManager->GetTexture(filename));
	m_bInitialised = true;
	
	C_SysContext::Get<RenderManager>()->AddRenderObject(this);
}
