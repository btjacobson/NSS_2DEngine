#include "AnimatedSprite_Comp.h"

AnimatedSpriteComp::AnimatedSpriteComp(float frameTime, bool loop, Entity* owner) : BaseComp(owner)
{

}

AnimatedSpriteComp::~AnimatedSpriteComp()
{
}

void AnimatedSpriteComp::Play(float dt)
{
}

void AnimatedSpriteComp::Stop()
{
}

void AnimatedSpriteComp::Reset()
{
}

sf::IntRect& AnimatedSpriteComp::GetCurrentFrame()
{
	// TODO: insert return statement here
	return _frames[0];
}
