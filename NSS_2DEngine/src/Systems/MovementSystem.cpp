#include "MovementSystem.h"

MovementSystem* MovementSystem::instance = nullptr;

MovementSystem* MovementSystem::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new MovementSystem();
    }

    return instance;
}

MovementSystem::~MovementSystem()
{
    delete instance;
    instance = nullptr;
}