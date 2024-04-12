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
	PhysicsComp* tComponent = _owner->GetComponent<PhysicsComp>();
	if (tComponent)
	{
		tComponent->SetDirection(sf::Vector2f(1, 0));
	}
}

void ControllerComp::MoveLeft()
{
	PhysicsComp* tComponent = _owner->GetComponent<PhysicsComp>();
	if (tComponent)
	{
		tComponent->SetDirection(sf::Vector2f(-1, 0));
	}
}

void ControllerComp::MoveUp()
{
	PhysicsComp* tComponent = _owner->GetComponent<PhysicsComp>();
	if (tComponent)
	{
		tComponent->SetDirection(sf::Vector2f(0, 1));
	}
}

void ControllerComp::MoveDown()
{
	PhysicsComp* tComponent = _owner->GetComponent<PhysicsComp>();
	if (tComponent)
	{
		tComponent->SetDirection(sf::Vector2f(0, -1));
	}
}

void ControllerComp::Stop()
{
	PhysicsComp* tComponent = _owner->GetComponent<PhysicsComp>();
	if (tComponent)
	{
		tComponent->Stop();
	}
}

void ControllerComp::Attack()
{

}
