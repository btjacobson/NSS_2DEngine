#include "Asset_Manager.h"

Asset_Manager* Asset_Manager::instance = nullptr;

Asset_Manager* Asset_Manager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Asset_Manager();
    }

    return instance;
}

Asset_Manager::~Asset_Manager()
{
    ClearTextures();

    delete instance;
    instance = nullptr;
}

void Asset_Manager::AddTexture(std::string name, std::string path)
{
    sf::Texture* tTexture = new sf::Texture();
    tTexture->loadFromFile(path);
    
    if (tTexture && textures.find(name) == textures.end())
    {
        textures.insert(std::make_pair(name, tTexture));
    }
}

void Asset_Manager::RemoveTexture(std::string name)
{
    if (textures.find(name) != textures.end())
    {
        delete textures.at(name);
        textures.at(name) = nullptr;
        textures.erase(name);
    }
}

void Asset_Manager::ClearTextures()
{
    auto itr = textures.begin();

    while (itr != textures.end())
    {
        delete itr->second;
        itr->second = nullptr;

        itr++;
    }

    textures.clear();
}

sf::Texture* Asset_Manager::GetTexture(std::string name)
{
    if (textures.find(name) != textures.end())
    {
        return textures.at(name);
    }
    else
    {
        return nullptr;
    }
}
