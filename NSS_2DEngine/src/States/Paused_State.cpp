#include "Paused_State.h"

Paused_State::Paused_State()
{
	Init();
}

Paused_State::~Paused_State()
{
	Cleanup();
}

void Paused_State::Init()
{
	SetActive(true);
}

void Paused_State::Cleanup()
{

}

void Paused_State::Update(float dt)
{

}

void Paused_State::Draw(sf::RenderWindow* window)
{

}

bool Paused_State::IsActive()
{
	return isActive;
}
