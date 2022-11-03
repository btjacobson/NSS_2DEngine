#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "../States/State.h"
#include "../States/Intro_State.h"
#include "../States/MainMenu_State.h"
#include "../States/Game_State.h"
#include "../States/Paused_State.h"

enum State_Type
{
	INTRO_STATE,
	MAINMENU_STATE,
	GAME_STATE,
	PAUSE_STATE
};

class State_Manager
{
public:
	static State_Manager* GetInstance();

	~State_Manager();

	void SwitchToState(State_Type stateType, bool popPrevious = false);

	void Update(float dt);
	void Draw(sf::RenderWindow* window);

private:
	State_Manager();
	State_Manager(State_Manager&) {}
	void operator=(State_Manager const&) const {}

	static State_Manager* instance;

	void PushState(State* state);
	void PopState();

	std::vector<State*> states;
};

#endif