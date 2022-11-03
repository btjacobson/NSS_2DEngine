#ifndef INTRO_STATE_H
#define INTRO_STATE_H

#include "State.h"

class Intro_State : public State
{
public:
	Intro_State();
	~Intro_State();

	virtual void Init() override;
	virtual void Cleanup() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* window) override;

	virtual bool IsActive() override;

private:
	void Finish();

	sf::Sprite background;
};

#endif
