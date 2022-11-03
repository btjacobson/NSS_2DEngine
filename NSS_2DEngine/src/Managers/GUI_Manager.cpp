#include "GUI_Manager.h"

GUI_Manager* GUI_Manager::instance = nullptr;

GUI_Manager* GUI_Manager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new GUI_Manager();
    }

    return instance;
}

GUI_Manager::~GUI_Manager()
{
    ClearGUIElements();

    delete instance;
    instance = nullptr;
}

void GUI_Manager::AddGUIElement(std::string name, GUI_Element* element)
{
    if (elements.find(name) == elements.end())
    {
        elements.insert(std::make_pair(name, element));
    }
}

void GUI_Manager::RemoveGUIElement(std::string name)
{
    if (elements.find(name) != elements.end())
    {
        delete elements.at(name);
        elements.at(name) = nullptr;
        elements.erase(name);
    }
}

void GUI_Manager::ClearGUIElements()
{
    auto itr = elements.begin();

    while (itr != elements.end())
    {
        delete itr->second;
        itr->second = nullptr;

        itr++;
    }

    elements.clear();
}

void GUI_Manager::Update(float dt)
{
    if (elements.size() > 0)
    {
        for (auto& element : elements)
        {
            element.second->Update(dt);
        }
    }
}

void GUI_Manager::Draw(sf::RenderWindow* window)
{
    if (elements.size() > 0)
    {
        for (auto& element : elements)
        {
            window->draw(*element.second->GetSprite());
        }
    }
}

GUI_Element* GUI_Manager::GetGUIElement(std::string name)
{
    if (elements.find(name) != elements.end())
    {
        return elements.at(name);
    }
    else
    {
        return nullptr;
    }
}
