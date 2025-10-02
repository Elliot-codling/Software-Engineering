#ifndef _ANIMATED_SPRITE_H
#define _ANIMATED_SPRITE_H

#include <vector>
#include <SFML/Graphics.hpp>

struct SpritesheetDef;

struct Animation
{
	Animation():m_Filename(nullptr), m_CurrentFrame(0), m_fps(0), m_CurrentTime(0.0f), m_TimePerFrame(0.0f), m_bLoop(false), m_bPaused(false), m_bFinished(false) {}

	const char* m_Filename;
	unsigned int m_CurrentFrame;
	int m_fps;
	std::vector<sf::IntRect> m_Frames;
	std::vector<sf::Vector2f> m_Origins;
	float m_CurrentTime;
	float m_TimePerFrame;
	bool m_bLoop;
	bool HasFinished() { return m_bFinished; }
	bool m_bPaused;
	bool m_bFinished;
	void Reset() { m_CurrentFrame = 0; m_CurrentTime = 0; m_bFinished = false; m_bPaused = false; }

};

class AnimatedSprite : public sf::Sprite
{
public:
	AnimatedSprite();
	~AnimatedSprite() override;

	void AddAnimation(int animationId, const char* filename, const std::vector<sf::IntRect>& frames, const std::vector<sf::Vector2f>& origins, int fps, bool loop = true);
	void AddAnimationFromSpriteSheetDef(int animationId, SpritesheetDef* pSpritesheetDef, const char* animationName, int fps, bool loop = true);

	void SetCurrentAnimation(int animationId);
	int GetCurrentAnimation() { return m_CurrentAnimation; }

	bool AnimationFinished();
	
	void Animate();

	int GetCurrentFrame(); 

	void SetVisible(bool visibility);

	void Pause();
	void Play();
	
private:	

	Animation& CurrentAnimation();

	bool m_bInitialised;

	std::map<int, Animation> m_Animations;
	int m_CurrentAnimation{};

	bool m_Visible;

};

#endif
