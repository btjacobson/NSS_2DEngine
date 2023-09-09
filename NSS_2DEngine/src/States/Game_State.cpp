#include "Game_State.h"

#include <iostream>

Game_State::Game_State() : map(sf::Vector2i(15, 15), 32)
{
	client = new Client();
	Init();
}

Game_State::~Game_State()
{
	Cleanup();
}

void Game_State::Init()
{
	SetActive(true);

	Asset_Manager::GetInstance()->AddTexture("player", "../assets/textures/entity sprites/player/player.png");
	Entity_Manager::GetInstance()->AddEntity<Player>("player", sf::Vector2f(200, 200), Asset_Manager::GetInstance()->GetTexture("player"));
	player = (Player*)Entity_Manager::GetInstance()->GetEntity("player");

	map.BuildMap();
	camera.FollowTarget(player);
}

void Game_State::Cleanup()
{
	Asset_Manager::GetInstance()->ClearTextures();
	Entity_Manager::GetInstance()->ClearEntities();
	Input_Manager::GetInstance()->ClearKeyboardBindings();
	Input_Manager::GetInstance()->ClearMouseBindings();

	delete client;

	client = nullptr;
	player = nullptr;
}

void Game_State::Update(float dt)
{
	map.Update(dt);
	camera.Update(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (!map.GetCollisionForTile(player->GetPosition().x, player->GetPosition().y - 4))
		{
			player->MoveUp();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (!map.GetCollisionForTile(player->GetPosition().x - 13, player->GetPosition().y))
		{
			player->MoveLeft();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (!map.GetCollisionForTile(player->GetPosition().x, player->GetPosition().y + 24))
		{
			player->MoveDown();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (!map.GetCollisionForTile(player->GetPosition().x + 12, player->GetPosition().y))
		{
			player->MoveRight();
		}
	}
}

void Game_State::Draw(sf::RenderWindow* window)
{
	map.Draw(window);
	camera.Draw(window);
}

bool Game_State::IsActive()
{
	return isActive;
}

void Game_State::ConnectToServer()
{
	if (!client->IsConnected())
	{
		sf::IpAddress ip = "127.0.0.1";
		PortNumber port = (unsigned)Network::ServerPort;

		client->SetServerInformation(ip, port);
		client->Setup(&Game_State::HandlePacket, this);
		commandThread = new sf::Thread(&Game_State::ProcessCommand, this);
		networkThread = new sf::Thread(&Game_State::HandleServer, this);

		if (client->Connect())
		{
			commandThread->launch();
			networkThread->launch();
		}
		else
		{
			std::cout << "Failed to connect" << std::endl;
		}
	}
}

void Game_State::HandlePacket(const PacketID& id, sf::Packet& packet, Client* client)
{
	if ((PacketType)id == PacketType::Message)
	{
		std::string message;
		packet >> message;

		std::cout << message << std::endl;
	}
	else if ((PacketType)id == PacketType::Disconnect)
	{
		client->Disconnect();
	}
}

void Game_State::ProcessCommand()
{
	while (client->IsConnected())
	{
		std::string str;
		std::getline(std::cin, str);

		if (str != "")
		{
			if (str == "!quit")
			{
				client->Disconnect();
				
				break;
			}

			sf::Packet packet;
			StampPacket(PacketType::Message, packet);
			packet << str;
			client->Send(packet);
		}
	}
}

void Game_State::HandleServer()
{
	clock.restart();

	while (client->IsConnected())
	{
		client->Update(clock.restart());
	}
}
