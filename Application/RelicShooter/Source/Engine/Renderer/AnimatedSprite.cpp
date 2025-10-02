#include "AnimatedSprite.h"
#include "../System/Assets/AssetManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "FrameTimer.h"
#include "RenderManager.h"

#include "../../Game/GameData/SpritesheetDef.h"

AnimatedSprite::AnimatedSprite()
	:m_bInitialised(false)
	,m_Visible(false)
{
	SetVisible(true);
}

void AnimatedSprite::SetVisible(const bool visibility)
{
	if (m_Visible == visibility)
		return; 
	m_Visible = visibility;
	if (m_Visible)
		C_SysContext::Get<RenderManager>()->AddRenderObject(this);
	else
		C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
}

AnimatedSprite::~AnimatedSprite()
{
	SetVisible(false);
}

void AnimatedSprite::AddAnimation(const int animationId, const char* filename, const std::vector<sf::IntRect>& frames, const std::vector<sf::Vector2f>& origins, const int fps, const bool loop)
{
	Animation animation;

	animation.m_Filename = filename;
	animation.m_Frames = frames;
	animation.m_Origins = origins;
	animation.m_fps = fps;
	animation.m_TimePerFrame = 1.0f / static_cast<float>(animation.m_fps);
	animation.m_bLoop = loop;

	m_Animations[animationId] = animation;
}

void AnimatedSprite::AddAnimationFromSpriteSheetDef(const int animationId, SpritesheetDef* pSpritesheetDef, const char* animationName, const int fps, bool loop)
{
	if (!pSpritesheetDef)
		return;

	std::vector<sf::IntRect> frames;
	std::vector<sf::Vector2f> origins;

	for (auto iter = pSpritesheetDef->m_pSpriteDefs.begin(); iter != pSpritesheetDef->m_pSpriteDefs.end(); ++iter)
	{
		//remove the frame number from the end of the sprite name
		std::string spriteNameFull = (*iter).m_Name;
		const std::size_t found = spriteNameFull.find_last_of('_');
		std::string spriteName = spriteNameFull.substr(0, found);

		//if this is a frame that we are looking for add it to the list
		if (spriteName == animationName)
		{
			sf::IntRect rect((*iter).m_PosX, (*iter).m_PosY, (*iter).m_Width, (*iter).m_Height);
			frames.push_back(rect);

			sf::Vector2f origin((*iter).m_PivotX * (*iter).m_Width, (*iter).m_PivotY * (*iter).m_Height);
			origins.push_back(origin);			
		}
	}

	AddAnimation(animationId, pSpritesheetDef->m_Filename.c_str(), frames, origins, fps, loop);
}

void AnimatedSprite::SetCurrentAnimation(const int animationId)
{
	const std::map<int, Animation>::iterator iter = m_Animations.find(animationId);

	if (iter != m_Animations.end())
	{
		if (m_bInitialised)
		{
			CurrentAnimation().Reset();
		}

		m_CurrentAnimation = animationId;

		auto* pAssetManager = C_SysContext::Get<AssetManager>();
		setTexture(pAssetManager->GetTexture(CurrentAnimation().m_Filename));

		if (CurrentAnimation().m_CurrentFrame < CurrentAnimation().m_Frames.size())
		{
			setTextureRect(CurrentAnimation().m_Frames[CurrentAnimation().m_CurrentFrame]);
			setOrigin(CurrentAnimation().m_Origins[CurrentAnimation().m_CurrentFrame]);
		}

		m_bInitialised = true;
	}
}

void AnimatedSprite::Animate()
{
	if (!m_bInitialised)
		return;


	//TODO: Move this inside the animation

	if (CurrentAnimation().m_bPaused)
		return;

	auto* pFrameTimer = C_SysContext::Get<FrameTimer>();
	const float delta = pFrameTimer->DeltaTime();
	CurrentAnimation().m_CurrentTime += delta;

	if (CurrentAnimation().m_CurrentTime >= CurrentAnimation().m_TimePerFrame)
	{
		CurrentAnimation().m_CurrentFrame++;
		CurrentAnimation().m_CurrentTime = 0;

		if (CurrentAnimation().m_CurrentFrame >= CurrentAnimation().m_Frames.size())
		{
			if (CurrentAnimation().m_bLoop)
			{
				CurrentAnimation().m_CurrentFrame = 0;
			}
			else
			{
				CurrentAnimation().m_CurrentFrame = CurrentAnimation().m_Frames.size() - 1;
				CurrentAnimation().m_bFinished = true;
			}
		}
	}

	if (CurrentAnimation().m_CurrentFrame < CurrentAnimation().m_Frames.size())
	{
		setTextureRect(CurrentAnimation().m_Frames[CurrentAnimation().m_CurrentFrame]);
		setOrigin(CurrentAnimation().m_Origins[CurrentAnimation().m_CurrentFrame]);
	}
	//TODO: sort out repeat
}

int AnimatedSprite::GetCurrentFrame()
{
	if (!m_bInitialised)
		return -1;

	return CurrentAnimation().m_CurrentFrame;
}

Animation& AnimatedSprite::CurrentAnimation()
{
	return m_Animations[m_CurrentAnimation];
}

bool AnimatedSprite::AnimationFinished()
{
	if (CurrentAnimation().HasFinished())
	{
		return true;
	}

	return false;
}

void AnimatedSprite::Pause()
{
	CurrentAnimation().m_bPaused = true;
}

void AnimatedSprite::Play()
{
	CurrentAnimation().m_bPaused = false;
}
