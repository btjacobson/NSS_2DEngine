#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>

#include <functional>
#include <iostream>

#include "../../../NSS_Shared/include/PacketTypes.h"
#include "../../../NSS_Shared/include/NetworkDefinitions.h"

#define CONNECT_TIMEOUT 5000

class Client;
using PacketHandler = std::function<void(const PacketID&, sf::Packet&, Client*)>;

class Client
{
public:
	Client();
	~Client();

	bool Connect();
	bool Disconnect();
	bool Send(sf::Packet& packet);
	bool IsConnected() const;

	void Listen();
	void SetTime(const sf::Time& time);
	void SetServerInformation(const sf::IpAddress& ip, const PortNumber& port);

	const sf::Time& GetTime() const;
	const sf::Time& GetLastHeartbeat() const;

	template<class T>
	void Setup(void(T::* handler)(const PacketID&, sf::Packet&, Client*), T* instance)
	{
		packetHandler = std::bind(handler, instance, std::placeholders::_1, std::placeholders::_2,
			std::placeholders::_3);
	}

	void Setup(void(*handler)(const PacketID&, sf::Packet&, Client*));
	void UnregisterPacketHandler();
	void Update(const sf::Time& time);
	void SetPlayerName(const std::string& name);

	sf::Mutex& GetMutex();

private:
	std::string playerName;
	sf::UdpSocket socket;
	sf::IpAddress serverIp;
	sf::Time serverTime;
	sf::Time lastHeartbeat;
	sf::Thread listenThread;
	sf::Mutex mutex;

	PortNumber serverPort;
	PacketHandler packetHandler;

	bool connected;
};

#endif
