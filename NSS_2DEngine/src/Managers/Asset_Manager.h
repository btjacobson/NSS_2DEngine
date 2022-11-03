#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>

#include <unordered_map>

class Asset_Manager
{
public:
	static Asset_Manager* GetInstance();

	~Asset_Manager();

	void AddTexture(std::string name, std::string path);
	void RemoveTexture(std::string name);
	void ClearTextures();

	sf::Texture* GetTexture(std::string name);

private:
	Asset_Manager() = default;
	Asset_Manager(Asset_Manager&) {}
	void operator=(Asset_Manager const&) const {}

	static Asset_Manager* instance;

	std::unordered_map<std::string, sf::Texture*> textures;
};

#endif
