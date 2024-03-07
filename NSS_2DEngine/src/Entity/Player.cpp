#include "Player.h"

#include <iostream>

Player::Player(sf::Vector2f position, sf::Texture* texture) : Entity(position, texture)
{
	speed = 200.0f;

	textureRect.left = 1;
	textureRect.top = 1;
	textureRect.width = 96;
	textureRect.height = 64;

	sprite.setTextureRect(textureRect);

	//Input_Manager::GetInstance()->AddMouseBinding(sf::Mouse::Button::Left, std::bind(&Player::Attack, this), true);
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
	velocity.y = -1;
}

void Player::MoveDown()
{
	velocity.y = 1;
}

void Player::MoveRight()
{
	velocity.x = 1;
}

void Player::MoveLeft()
{
	velocity.x = -1;
}

void Player::Stop()
{
	SetVelocity(sf::Vector2f(0, 0));
}

void Player::Attack()
{
	textureRect.left += 16;
	if (textureRect.left > 864)
	{
		textureRect.left = 0;
	}

	sprite.setTextureRect(textureRect);

	std::cout << "Left: " << textureRect.left << std::endl;
}
