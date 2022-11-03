#include "State_Manager.h"

State_Manager* State_Manager::instance = nullptr;

State_Manager::State_Manager()
{
	SwitchToState(INTRO_STATE, false);
}

State_Manager* State_Manager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new State_Manager();
	}

	return instance;
}

State_Manager::~State_Manager()
{
	for (auto& state : states)
	{
		delete state;
		state = nullptr;
	}

	states.clear();
}

void State_Manager::SwitchToState(State_Type stateType, bool popPrevious)
{
	if (popPrevious)
	{
		states.pop_back();
	}

	switch (stateType)
	{
	case INTRO_STATE:
		PushState(new Intro_State());
		break;

	case MAINMENU_STATE:
		PushState(new MainMenu_State());
		break;

	case GAME_STATE:
		PushState(new Game_State());
		break;

	case PAUSE_STATE:
		PushState(new Paused_State());
		break;

	default:
		break;
	}
}

void State_Manager::Update(float dt)
{
	if (states.size() > 0)
	{
		for (auto& state : states)
		{
			if (state->IsActive())
			{
				state->Update(dt);
			}
		}
	}
}

void State_Manager::Draw(sf::RenderWindow* window)
{
	if (states.size() > 0)
	{
		for (auto& state : states)
		{
			if (state->IsActive())
			{
				state->Draw(window);
			}
		}
	}
}

void State_Manager::PushState(State* state)
{
	states.push_back(state);
}

void State_Manager::PopState()
{
	if (states.size() > 0)
	{
		states.pop_back();
	}
}
