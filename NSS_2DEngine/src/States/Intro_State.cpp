#include "Intro_State.h"

#include <iostream>

#include "../Managers/State_Manager.h"

Intro_State::Intro_State()
{
	Init();
}

Intro_State::~Intro_State()
{
	Cleanup();
}

void Intro_State::Init()
{
	Asset_Manager::GetInstance()->AddTexture("intro", "../Assets/textures/intro.png");
	Timer_Manager::GetInstance()->AddTimer(4, std::bind(&Intro_State::Finish, this));

	background.setTexture(*Asset_Manager::GetInstance()->GetTexture("intro"));
	SetActive(true);
}

void Intro_State::Cleanup()
{
	Asset_Manager::GetInstance()->RemoveTexture("intro");
}

void Intro_State::Update(float dt)
{

}

void Intro_State::Draw(sf::RenderWindow* window)
{
	window->draw(background);
}

bool Intro_State::IsActive()
{
	return isActive;
}

void Intro_State::Finish()
{
	State_Manager::GetInstance()->SwitchToState(GAME_STATE, true);
}
