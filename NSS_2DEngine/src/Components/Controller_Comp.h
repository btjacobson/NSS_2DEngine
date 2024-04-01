#ifndef CONTROLLER_COMP_H
#define CONTROLLER_COMP_H

#include <iostream>

#include "../Managers/Input_Manager.h"

#include "Base_Comp.h"
#include "Transform_Comp.h"

class ControllerComp : public BaseComp
{
public:
	ControllerComp();
	~ControllerComp();

	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void Stop();
	void Attack();

private:

};

#endif
