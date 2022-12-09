#include "Player.h"

Player::Player(sf::Vector2f position, sf::Texture* texture) : Entity(position, texture)
{
	Input_Manager::GetInstance()->AddKeyboardBinding(sf::Keyboard::W,
		std::bind(&Player::MoveUp, this), std::bind(&Player::Stop, this));

	Input_Manager::GetInstance()->AddKeyboardBinding(sf::Keyboard::A,
		std::bind(&Player::MoveLeft, this), std::bind(&Player::Stop, this));

	Input_Manager::GetInstance()->AddKeyboardBinding(sf::Keyboard::S,
		std::bind(&Player::MoveDown, this), std::bind(&Player::Stop, this));

	Input_Manager::GetInstance()->AddKeyboardBinding(sf::Keyboard::D,
		std::bind(&Player::MoveRight, this), std::bind(&Player::Stop, this));
}

Player::~Player()
{

}

void Player::SetVelocity(sf::Vector2f vel)
{
	velocity = vel;
}

void Player::MoveUp()
{
	SetVelocity(sf::Vector2f(0, -1));
}

void Player::MoveDown()
{
	SetVelocity(sf::Vector2f(0, 1));
}

void Player::MoveRight()
{
	SetVelocity(sf::Vector2f(1, 0));
}

void Player::MoveLeft()
{
	SetVelocity(sf::Vector2f(-1, 0));
}

void Player::Stop()
{
	SetVelocity(sf::Vector2f(0, 0));
}
