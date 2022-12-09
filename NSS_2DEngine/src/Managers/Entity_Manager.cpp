#include "Entity_Manager.h"

Entity_Manager* Entity_Manager::instance = nullptr;

Entity_Manager* Entity_Manager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Entity_Manager();
    }

    return instance;
}

Entity_Manager::~Entity_Manager()
{
    ClearEntities();

    delete instance;
    instance = nullptr;
}

void Entity_Manager::RemoveEntity(std::string name)
{
    if (entities.find(name) != entities.end())
    {
        delete entities.at(name);
        entities.at(name) = nullptr;
        entities.erase(name);
    }
}

void Entity_Manager::ClearEntities()
{
    auto itr = entities.begin();

    while (itr != entities.end())
    {
        delete itr->second;
        itr->second = nullptr;

        itr++;
    }

    entities.clear();
}

void Entity_Manager::Update(float dt)
{
    if (entities.size() > 0)
    {
        for (auto& entity : entities)
        {
            entity.second->Update(dt);
        }
    }
}

void Entity_Manager::Draw(sf::RenderWindow* window)
{
    if (entities.size() > 0)
    {
        for (auto& entity : entities)
        {
            window->draw(*entity.second->GetSprite());
        }
    }
}

Entity* Entity_Manager::GetEntity(std::string name)
{
    if (entities.find(name) != entities.end())
    {
        return entities.at(name);
    }
    else
    {
        return nullptr;
    }
}
