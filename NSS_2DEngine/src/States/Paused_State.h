#ifndef PAUSED_STATE_H
#define PAUSED_STATE_H

#include "State.h"

class Paused_State : public State
{
public:
	Paused_State();
	~Paused_State();

	virtual void Init() override;
	virtual void Cleanup() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* window) override;

	virtual bool IsActive() override;

private:

};

#endif
