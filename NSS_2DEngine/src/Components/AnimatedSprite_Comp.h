#ifndef ANIMATED_SPRITE_COMP_H
#define ANIMATED_SPRITE_COMP_H

#include <SFML/Graphics/Sprite.hpp>

#include "Base_Comp.h"

class AnimatedSpriteComp : public BaseComp
{
public:
	AnimatedSpriteComp(float frameTime, bool loop, Entity* owner);
	~AnimatedSpriteComp();

	void Play(float dt);
	void Stop();
	void Reset();

	sf::IntRect& GetCurrentFrame();

private:
	std::vector<sf::IntRect> _frames;
	float _frameTime;
	float _currentFrameTime;
	bool _loop;
	int _currentFrame; 
};

#endif 
