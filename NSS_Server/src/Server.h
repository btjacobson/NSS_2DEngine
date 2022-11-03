#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <SFML/System/Time.hpp>

#include <unordered_map>
#include <functional>
#include <iostream>

#include "../../NSS_Shared/include/PacketTypes.h"
#include "../../NSS_Shared/include/NetworkDefinitions.h"

#define HEARTBEAT_INTERVAL 1000
#define HEARTBEAT_RETRIES 5

struct ClientInfo
{
	sf::IpAddress clientIp;
	PortNumber clientPort;
	sf::Time lastHeartbeat;
	sf::Time heartbeatSent;
	bool heartbeatWaiting;
	unsigned short heartbeatRetry;
	unsigned int ping;

	ClientInfo(const sf::IpAddress& ip, const PortNumber& port, const sf::Time& heartbeat) :
		clientIp(ip), clientPort(port), lastHeartbeat(heartbeat), heartbeatWaiting(false), heartbeatRetry(0), ping(0)
	{

	}

	ClientInfo& operator=(const ClientInfo& rhs)
	{
		clientIp = rhs.clientIp;
		clientPort = rhs.clientPort;
		lastHeartbeat = rhs.lastHeartbeat;
		heartbeatSent = rhs.heartbeatSent;
		heartbeatWaiting = rhs.heartbeatWaiting;
		heartbeatRetry = rhs.heartbeatRetry;
		ping = rhs.ping;

		return *this;
	}
};

using Clients = std::unordered_map<ClientID, ClientInfo>;

class Server;
using PacketHandler = std::function<void(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*)>;
using TimeoutHandler = std::function<void(const ClientID&)>;

class Server
{
public:
	template<class T>
	Server(void(T::* handler)(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*),
		T* instance) : listenThread(&Server::Listen, this)
	{
		packetHandler = std::bind(handler, instance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
			std::placeholders::_4, std::placeholders::_5);
	}

	Server(void(*handler)(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*));
	~Server();

	template<class T>
	void BindTimeoutHandler(void(T::* handler)(const ClientID&), T* instance)
	{
		timeoutHandler = std::bind(handler, instance, std::placeholders::_1);
	}
	
	void BindTimeoutHandler(void(*handler)(const ClientID&));

	bool Send(const ClientID& id, sf::Packet& packet);
	bool Send(sf::IpAddress& ip, const PortNumber& port, sf::Packet& packet);
	void Broadcast(sf::Packet& packet, const ClientID& ignore = ClientID(Network::NullID));

	void Listen();
	void Update(const sf::Time& time);

	ClientID AddClient(const sf::IpAddress& ip, const PortNumber& port);
	ClientID GetClientID(const sf::IpAddress& ip, const PortNumber& port);

	bool HasClient(const ClientID& id);
	bool HasClient(const sf::IpAddress& ip, const PortNumber& port);
	bool GetClientInfo(const ClientID& id, ClientInfo& info);
	bool RemoveClient(const ClientID& id);
	bool RemoveClient(const sf::IpAddress& ip, const PortNumber& port);

	void DisconnectAll();
	bool Start();
	bool Stop();
	bool IsRunning();

	unsigned int GetClientCount();
	std::string GetClientList();

	sf::Mutex& GetMutex();

private:
	void Setup();

	ClientID lastId;

	sf::UdpSocket incoming;
	sf::UdpSocket outgoing;

	PacketHandler packetHandler;
	TimeoutHandler timeoutHandler;

	Clients clients;
	sf::Time serverTime;

	bool running;

	sf::Thread listenThread;
	sf::Mutex mutex;

	size_t totalSent;
	size_t totalReceived;
};

#endif
