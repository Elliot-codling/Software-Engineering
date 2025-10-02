#include "AnimationStateMachine.h"
#include "../../Renderer/AnimatedSprite.h"


AnimationStateMachine::AnimationStateMachine()
	:m_CurrentState(-1)
{

}

AnimationStateMachine::~AnimationStateMachine()
= default;

void AnimationStateMachine::Initialise()
{

}

void AnimationStateMachine::Update()
{
	if (m_CurrentState == -1)
		return;

	const auto iter = m_Animations.find(m_CurrentState);
	if (iter != m_Animations.end())
	{
		AnimatedSprite* pAnimatedSprite = iter->second;
		pAnimatedSprite->Animate();
	}
}

void AnimationStateMachine::AddAnimationState(const int state, AnimatedSprite* pAnimatedSprite)
{
	if (!pAnimatedSprite)
		return;

	if (!AnimationStateExists(state))
	{
		m_Animations[state] = pAnimatedSprite;
	}
}

void AnimationStateMachine::TransitionToState(const int state)
{
	if (AnimationStateExists(state))
	{
		const int previousAnimationState = m_CurrentState;
		m_CurrentState = state;

		SetAnimationActive(previousAnimationState, false);
		ResetAnimation();

		SetAnimationActive(m_CurrentState, true);
	}
}

void AnimationStateMachine::ResetAnimation()
{

}

bool AnimationStateMachine::AnimationStateExists(const int state)
{
	if (m_Animations.find(state) != m_Animations.end())
		return true;

	return false;
}

void AnimationStateMachine::SetAnimationActive(const int state, const bool active)
{
	const std::map<int, AnimatedSprite*>::iterator iter = m_Animations.find(state);
	if (iter != m_Animations.end())
	{
		AnimatedSprite* pAnimatedSprite = iter->second;
		pAnimatedSprite->SetVisible(active);
	}
}