#ifndef PLAYER_H
#define PLAYER_H

#include "../Managers/Input_Manager.h"
#include "../Entity/Entity.h"

#include <iostream>

class Player : public Entity
{
public:
	Player();
	~Player();

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void Stop();

	void Attack();

private:

};

#endif