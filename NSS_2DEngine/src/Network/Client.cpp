#include "Client.h"

Client::Client() : listenThread(&Client::Listen, this)
{
	connected = false;
}

Client::~Client()
{
	socket.unbind();
}

bool Client::Connect()
{
	if (connected)
	{
		return false;
	}

	socket.bind(sf::Socket::AnyPort);
	std::cout << "Bound client to port: " << socket.getLocalPort() << std::endl;

	sf::Packet packet;
	StampPacket(PacketType::Connect, packet);
	packet << playerName;

	if (socket.send(packet, serverIp, serverPort) != sf::Socket::Done)
	{
		socket.unbind();

		return false;
	}

	socket.setBlocking(false);
	packet.clear();

	sf::IpAddress recvIp;
	PortNumber recvPort;
	sf::Clock timer;
	timer.restart();

	std::cout << "Attempting to connect to: " << serverIp << ":" << serverPort << std::endl;

	while (timer.getElapsedTime().asMilliseconds() < CONNECT_TIMEOUT)
	{
		sf::Socket::Status status = socket.receive(packet, recvIp, recvPort);
		if (status != sf::Socket::Done)
		{
			continue;
		}

		if (recvIp != serverIp)
		{
			continue;
		}

		PacketID id;
		if (!(packet >> id))
		{
			break;
		}

		if ((PacketType)id != PacketType::Connect)
		{
			continue;
		}

		packetHandler(id, packet, this);
		connected = true;
		socket.setBlocking(true);
		lastHeartbeat = serverTime;
		listenThread.launch();

		return true;
	}

	std::cout << "Connection attempt failed server information: " << serverIp << ":" << serverPort << std::endl;
	socket.unbind();
	socket.setBlocking(true);

	return false;
}

bool Client::Disconnect()
{
	if (!connected)
	{
		return false;
	}

	sf::Packet packet;
	StampPacket(PacketType::Disconnect, packet);
	sf::Socket::Status status = socket.send(packet, serverIp, serverPort);
	connected = false;
	socket.unbind();

	if (status != sf::Socket::Done)
	{
		return false;
	}

	return true;
}

bool Client::Send(sf::Packet& packet)
{
	if (!connected)
	{
		return false;
	}

	if (socket.send(packet, serverIp, serverPort) != sf::Socket::Done)
	{
		return false;
	}

	return true;
}

bool Client::IsConnected() const
{
	return connected;
}

void Client::Listen()
{
	sf::Packet packet;
	sf::IpAddress recvIp;
	PortNumber recvPort;

	std::cout << "Beginning to listen..." << std::endl;

	while (connected)
	{
		packet.clear();
		sf::Socket::Status status = socket.receive(packet, recvIp, recvPort);
		if (status != sf::Socket::Done)
		{
			if (connected)
			{
				std::cout << "Failed to receive a packet from " << recvIp << ":" << recvPort << ". Status: "<< status << std::endl;
				
				continue;
			}
			else
			{
				std::cout << "Socket unbound" << std::endl;

				break;
			}
		}

		if (recvIp != serverIp)
		{
			std::cout << "Invalid packet received: invalid origin" << std::endl;

			continue;
		}

		PacketID pid;
		if (!(packet >> pid))
		{
			std::cout << "Invalid packet recevied: unable to extract id" << std::endl;

			continue;
		}

		PacketType ptid = (PacketType)pid;
		if (ptid < PacketType::Disconnect || ptid >= PacketType::OutOfBounds)
		{
			std::cout << "Invalid packet received: id is out of bounds" << std::endl;

			continue;
		}

		if (ptid == PacketType::Heartbeat)
		{
			sf::Packet hPacket;
			StampPacket(PacketType::Heartbeat, hPacket);

			if (socket.send(hPacket, serverIp, serverPort) != sf::Socket::Done)
			{
				std::cout << "Failed sending a heartbeat" << std::endl;
			}

			sf::Int32 timestamp;
			packet >> timestamp;
			SetTime(sf::milliseconds(timestamp));
			lastHeartbeat = serverTime;
		}
		else if (packetHandler)
		{
			packetHandler((PacketID)ptid, packet, this);
		}
	}

	std::cout << "... Listening stopped" << std::endl;
}

void Client::SetTime(const sf::Time& time)
{
	serverTime = time;
}

void Client::SetServerInformation(const sf::IpAddress& ip, const PortNumber& port)
{
	serverIp = ip;
	serverPort = port;
}

const sf::Time& Client::GetTime() const
{
	return serverTime;
}

const sf::Time& Client::GetLastHeartbeat() const
{
	return lastHeartbeat;
}

void Client::Setup(void(*handler)(const PacketID&, sf::Packet&, Client*))
{
	packetHandler = std::bind(handler, std::placeholders::_1, std::placeholders::_2,
		std::placeholders::_3);
}

void Client::UnregisterPacketHandler()
{
	packetHandler = nullptr;
}

void Client::Update(const sf::Time& time)
{
	if (!connected)
	{
		return;
	}

	serverTime += time;

	if (serverTime.asMilliseconds() < 0)
	{
		serverTime -= sf::milliseconds(sf::Int32(Network::HighestTimestamp));
		lastHeartbeat = serverTime;

		return;
	}

	if (serverTime.asMilliseconds() - lastHeartbeat.asMilliseconds() >= sf::Int32(Network::ClientTimeout))
	{
		std::cout << "Server connection timed out" << std::endl;
		Disconnect();
	}
}

void Client::SetPlayerName(const std::string& name)
{
	playerName = name;
}

sf::Mutex& Client::GetMutex()
{
	return mutex;
}
