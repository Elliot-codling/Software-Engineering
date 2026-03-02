#ifndef _ANIMATED_SPRITE_H
#define _ANIMATED_SPRITE_H

#include <vector>
#include <SFML/Graphics.hpp>

struct SpritesheetDef;

struct Animation
{
	Animation():m_Filename(nullptr), m_CurrentFrame(0), m_fps(0), m_CurrentTime(0.0f), m_TimePerFrame(0.0f), m_bLoop(false), m_bPaused(false), m_bFinished(false) {}

	const char* m_Filename;
	int m_CurrentFrame;
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
	~AnimatedSprite();

	void Initialse(bool isUIObject = false);
	void Animate();

	sf::Vector2i GetFrameSize();
	sf::Sprite* GetSprite();
	sf::Sprite* GetSprite(int animation, int frame);

	// --- Get functions ---
	bool AnimationFinished();
	int GetCurrentAnimation() { return m_CurrentAnimation; }
	int GetNumberOfFrames() { return CurrentAnimation().m_Frames.size(); }


	// --- Animation controls
	void SetFPS(float fps);
	void Pause();
	void Play();
	void SetVisible(bool visibility);
	
private:	
	Animation& CurrentAnimation();

	bool m_bInitialised;

	std::map<int, Animation> m_Animations;
	int m_CurrentAnimation = -1;

	bool m_Visible;
	bool m_isUIObject = false;

protected:
	void AddAnimation(int animationId, const char* filename, std::vector<sf::IntRect>& frames, std::vector<sf::Vector2f>& origins, int fps, bool loop = true);
	void AddAnimationFromSpriteSheetDef(int animationId, SpritesheetDef* pSpritesheetDef, const char* animationName, int fps, bool loop = true);
	virtual void SetCurrentAnimation(int animationId);
	
	int GetCurrentFrame(); 
};

#endif
