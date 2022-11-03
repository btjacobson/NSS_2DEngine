#include <SFML/Network.hpp>

#include <iostream>

#include "Server.h"

void Handler(sf::IpAddress& ip, const PortNumber& port, const PacketID& id, sf::Packet& packet, Server* server)
{
	ClientID cid = server->GetClientID(ip, port);
	if (cid >= 0)
	{
		if ((PacketType)id == PacketType::Disconnect)
		{
			server->RemoveClient(ip, port);
			sf::Packet packet;
			StampPacket(PacketType::Message, packet);
			std::string message;
			message = "Client left " + ip.toString() + ":" + std::to_string(port);
			packet << message;
			server->Broadcast(packet, cid);
		}
		else if ((PacketType)id == PacketType::Message)
		{
			std::string receivedMessage;
			packet >> receivedMessage;
			std::string message = ip.toString() + ":" + std::to_string(port) + " :" + receivedMessage;
			sf::Packet packet;
			StampPacket(PacketType::Message, packet);
			packet << message;
			server->Broadcast(packet, cid);
		}
	}
	else
	{
		if ((PacketType)id == PacketType::Connect)
		{
			ClientID ccid = server->AddClient(ip, port);
			sf::Packet packet;
			StampPacket(PacketType::Connect, packet);
			server->Send(ccid, packet);
		}
	}
}

void ProcessCommand(Server* server)
{
	while (server->IsRunning())
	{
		std::string str;
		std::getline(std::cin, str);
		
		if (str == "!quit")
		{
			server->Stop();
			break;

		}
		else if (str == "dc")
		{
			server->DisconnectAll();
			std::cout << "DC..." << std::endl;
		}
		else if (str == "list")
		{
			std::cout << server->GetClientCount() << " clients online:" << std::endl;
			std::cout << server->GetClientList() << std::endl;
		}
	}
}

int main()
{
	Server server(Handler);

	if (server.Start())
	{
		sf::Thread commandThread(&ProcessCommand, &server);
		commandThread.launch();

		sf::Clock clock;
		clock.restart();
		while (server.IsRunning())
		{
			server.Update(clock.restart());
		}

		std::cout << "Stopping server..." << std::endl;
	}

	return 0;
}