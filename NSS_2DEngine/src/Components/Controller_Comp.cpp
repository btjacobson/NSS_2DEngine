#include "Controller_Comp.h"

#include "../Entity/Entity.h"

ControllerComp::ControllerComp()
{
	Input_Manager::GetInstance()->AddKeyboardBinding(
		sf::Keyboard::W, 
		std::bind(&ControllerComp::MoveUp, this),
		std::bind(&ControllerComp::Stop, this));

	Input_Manager::GetInstance()->AddKeyboardBinding(
		sf::Keyboard::S,
		std::bind(&ControllerComp::MoveDown, this),
		std::bind(&ControllerComp::Stop, this));

	Input_Manager::GetInstance()->AddKeyboardBinding(
		sf::Keyboard::A,
		std::bind(&ControllerComp::MoveLeft, this),
		std::bind(&ControllerComp::Stop, this));

	Input_Manager::GetInstance()->AddKeyboardBinding(
		sf::Keyboard::D,
		std::bind(&ControllerComp::MoveRight, this),
		std::bind(&ControllerComp::Stop, this));
}

ControllerComp::~ControllerComp()
{
	Input_Manager::GetInstance()->RemoveKeyboardBinding(sf::Keyboard::W);
	Input_Manager::GetInstance()->RemoveKeyboardBinding(sf::Keyboard::S);
	Input_Manager::GetInstance()->RemoveKeyboardBinding(sf::Keyboard::A);
	Input_Manager::GetInstance()->RemoveKeyboardBinding(sf::Keyboard::D);
}

void ControllerComp::MoveRight()
{
	auto tComponent = _owner->GetComponent<PhysicsComp>();
}

void ControllerComp::MoveLeft()
{
	auto tComponent = _owner->GetComponent<PhysicsComp>();
}

void ControllerComp::MoveUp()
{
	std::cout << "MoveUp" << std::endl;
	auto tComponent = _owner->GetComponent<PhysicsComp>();
}

void ControllerComp::MoveDown()
{
	std::cout << "MoveDown" << std::endl;
	auto tComponent = _owner->GetComponent<PhysicsComp>();
}

void ControllerComp::Stop()
{
	std::cout << "Stop" << std::endl;
	auto tComponent = _owner->GetComponent<PhysicsComp>();
}

void ControllerComp::Attack()
{

}
