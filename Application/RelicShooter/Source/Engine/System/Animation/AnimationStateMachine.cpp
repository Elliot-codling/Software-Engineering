#include "AnimationStateMachine.h"
#include "../../Renderer/AnimatedSprite.h"


AnimationStateMachine::AnimationStateMachine()
	:m_CurrentState(-1)
{

}

AnimationStateMachine::~AnimationStateMachine()
{

}

void AnimationStateMachine::Initialise()
{

}

void AnimationStateMachine::Update()
{
	if (m_CurrentState == -1)
		return;

	std::map<int, AnimatedSprite*>::iterator iter = m_Animations.find(m_CurrentState);
	if (iter != m_Animations.end())
	{
		AnimatedSprite* pAnimatedSprite = iter->second;
		pAnimatedSprite->Animate();
	}
}

void AnimationStateMachine::AddAnimationState(int state, AnimatedSprite* pAnimatedSprite)
{
	if (!pAnimatedSprite)
		return;

	if (!AnimationStateExists(state))
	{
		m_Animations[state] = pAnimatedSprite;
	}
}

void AnimationStateMachine::TransitionToState(int state)
{
	if (AnimationStateExists(state))
	{
		int previousAnimationState = m_CurrentState;
		m_CurrentState = state;

		SetAnimationActive(previousAnimationState, false);
		ResetAnimation(previousAnimationState);

		SetAnimationActive(m_CurrentState, true);
	}
}

void AnimationStateMachine::ResetAnimation(int state)
{

}

bool AnimationStateMachine::AnimationStateExists(int state)
{
	if (m_Animations.find(state) != m_Animations.end())
		return true;

	return false;
}

void AnimationStateMachine::SetAnimationActive(int state, bool active)
{
	std::map<int, AnimatedSprite*>::iterator iter = m_Animations.find(state);
	if (iter != m_Animations.end())
	{
		AnimatedSprite* pAnimatedSprite = iter->second;
		pAnimatedSprite->SetVisible(active);
	}
}