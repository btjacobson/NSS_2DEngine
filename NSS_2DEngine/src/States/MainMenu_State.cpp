#include "MainMenu_State.h"

#include <iostream>

MainMenu_State::MainMenu_State()
{
	Init();
}

MainMenu_State::~MainMenu_State()
{
	Cleanup();
}

void MainMenu_State::Init()
{
	SetActive(true);

	Asset_Manager::GetInstance()->AddTexture("button", "../Assets/textures/gui/testbutton.png");
	GUI_Manager::GetInstance()->AddGUIElement("test", new Button(sf::Vector2f(100, 100), sf::Vector2f(200, 60)));
	GUI_Manager::GetInstance()->GetGUIElement("test")->SetSprite(Asset_Manager::GetInstance()->GetTexture("button"));
}

void MainMenu_State::Cleanup()
{
	Asset_Manager::GetInstance()->RemoveTexture("button");
	GUI_Manager::GetInstance()->RemoveGUIElement("test");
}

void MainMenu_State::Update(float dt)
{

}

void MainMenu_State::Draw(sf::RenderWindow* window)
{

}

bool MainMenu_State::IsActive()
{
	return isActive;
}
