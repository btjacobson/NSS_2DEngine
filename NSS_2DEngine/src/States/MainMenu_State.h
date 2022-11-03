#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "State.h"

class MainMenu_State : public State
{
public:
	MainMenu_State();
	~MainMenu_State();

	virtual void Init() override;
	virtual void Cleanup() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow* window) override;

	virtual bool IsActive() override;

private:

};

#endif
