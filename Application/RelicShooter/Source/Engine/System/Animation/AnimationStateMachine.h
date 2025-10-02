#ifndef _ANIMATION_STATE_MACHINE_H
#define _ANIMATION_STATE_MACHINE_H

#include <map>

class AnimatedSprite;


class AnimationStateMachine
{
public:
	AnimationStateMachine();
	~AnimationStateMachine();

	static void Initialise();
	void Update();

	void AddAnimationState(int state, AnimatedSprite* pAnimatedSprite);
	void TransitionToState(int state);

	bool AnimationStateExists(int state);
	
	int GetCurrentAnimationState() { return m_CurrentState; }

private:
	static void ResetAnimation();
	void SetAnimationActive(int state, bool active = true);

	int m_CurrentState;
	std::map<int, AnimatedSprite*> m_Animations;
};

#endif
