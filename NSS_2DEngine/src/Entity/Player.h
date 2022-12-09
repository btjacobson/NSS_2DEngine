#ifndef PLAYER_H
#define PLAYER_H

#include "../Managers/Input_Manager.h"
#include "../Entity/Entity.h"

class Player : public Entity
{
public:
	Player(sf::Vector2f position, sf::Texture* texture);
	~Player();

	void SetVelocity(sf::Vector2f vel) override;

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void Stop();

private:

};

#endif