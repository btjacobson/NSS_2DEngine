#include "Server.h"

Server::Server(void(*handler)(sf::IpAddress&, const PortNumber&, const PacketID&, sf::Packet&, Server*))
    : listenThread(&Server::Listen, this), running(false)
{
    packetHandler = std::bind(handler, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
        std::placeholders::_4, std::placeholders::_5);
}

Server::~Server()
{
    Stop();
}

void Server::BindTimeoutHandler(void(*handler)(const ClientID&))
{
    timeoutHandler = std::bind(handler, std::placeholders::_1);
}

bool Server::Send(const ClientID& id, sf::Packet& packet)
{
    sf::Lock lock(mutex);
    auto client = clients.find(id);

    if (client == clients.end())
    {
        return false;
    }

    if (outgoing.send(packet, client->second.clientIp, client->second.clientPort) != sf::Socket::Done)
    {
        std::cout << "Error sending packet" << std::endl;
        return false;
    }

    totalSent += packet.getDataSize();

    return true;
}

bool Server::Send(sf::IpAddress& ip, const PortNumber& port, sf::Packet& packet)
{
    if (outgoing.send(packet, ip, port) != sf::Socket::Done)
    {
        return false;
    }

    totalSent += packet.getDataSize();

    return true;
}

void Server::Broadcast(sf::Packet& packet, const ClientID& ignore)
{
    sf::Lock lock(mutex);
    for (auto& client : clients)
    {
        if (client.first != ignore)
        {
            if (outgoing.send(packet, client.second.clientIp, client.second.clientPort) != sf::Socket::Done)
            {
                std::cout << "Error broadcasting a packet to client: " << client.first << std::endl;
                
                continue;
            }
            totalSent += packet.getDataSize();
        }
    }
}

void Server::Listen()
{
    sf::IpAddress ip;
    PortNumber port;
    sf::Packet packet;
    
    std::cout << "Beginning to listen..." << std::endl;

    while (running)
    {
        packet.clear();

        sf::Socket::Status status = incoming.receive(packet, ip, port);
        if (status != sf::Socket::Done)
        {
            if (running)
            {
                std::cout << "Error receiving packet from: " << ip << ":" << port << ". Code: " << status << std::endl;

                continue;
            }
            else
            {
                std::cout << "Socket unbound" << std::endl;
            }
        }

        totalReceived += packet.getDataSize();

        PacketID pid;
        if (!(packet >> pid))
        {
            std::cout << "Invalid packet received: unable to extract id" << std::endl;

            continue;
        }

        PacketType id = (PacketType)pid;
        if (id < PacketType::Disconnect || id >= PacketType::OutOfBounds)
        {
            std::cout << "Invalid packet received: id is out of bounds" << std::endl;

            continue;
        }

        if (id == PacketType::Heartbeat)
        {
            bool clientFound = false;
            sf::Lock lock(mutex);

            for (auto& client : clients)
            {
                if (client.second.clientIp != ip || client.second.clientPort != port)
                {
                    continue;
                }

                clientFound = true;
                if (!client.second.heartbeatWaiting)
                {
                    std::cout << "Invalid heartbeat packet received" << std::endl;

                    break;
                }

                client.second.ping = serverTime.asMilliseconds() - client.second.heartbeatSent.asMilliseconds();
                client.second.lastHeartbeat = serverTime;
                client.second.heartbeatWaiting = false;
                client.second.heartbeatRetry = 0;

                break;
            }

            if (!clientFound)
            {
                std::cout << "Heartbeat from unknown client received" << std::endl;
            }
        }
        else if (packetHandler)
        {
            packetHandler(ip, port, (PacketID)id, packet, this);
        }
    }

    std::cout << "...Listening stopped" << std::endl;
}

void Server::Update(const sf::Time& time)
{
    serverTime += time;
    if (serverTime.asMilliseconds() < 0)
    {
        serverTime -= sf::milliseconds(sf::Int32(Network::HighestTimestamp));
        sf::Lock lock(mutex);

        for (auto& client : clients)
        {
            client.second.lastHeartbeat = sf::milliseconds(std::abs(client.second.lastHeartbeat.asMilliseconds() - sf::Int32(Network::HighestTimestamp)));
        }
    }

    sf::Lock lock(mutex);
    for (auto client = clients.begin(); client != clients.end();)
    {
        sf::Int32 elapsed = serverTime.asMilliseconds() - client->second.lastHeartbeat.asMilliseconds();
        if (elapsed >= HEARTBEAT_INTERVAL)
        {
            if (elapsed >= sf::Int32(Network::ClientTimeout) || client->second.heartbeatRetry > HEARTBEAT_RETRIES)
            {
                std::cout << "Client " << client->first << " has timed out" << std::endl;
                
                if (timeoutHandler)
                {
                    timeoutHandler(client->first);
                }

                client = clients.erase(client);

                continue;
            }

            if (!client->second.heartbeatWaiting || (elapsed >= HEARTBEAT_INTERVAL * (client->second.heartbeatRetry + 1)))
            {
                if (client->second.heartbeatRetry >= 3)
                {
                    std::cout << "Retry (" << client->second.heartbeatRetry << ") heartbeat for client " << client->first << std::endl;
                }

                sf::Packet heartbeat;
                StampPacket(PacketType::Heartbeat, heartbeat);
                heartbeat << serverTime.asMilliseconds();
                Send(client->first, heartbeat);

                if (client->second.heartbeatRetry == 0)
                {
                    client->second.heartbeatSent = serverTime;
                }

                client->second.heartbeatWaiting = true;
                ++client->second.heartbeatRetry;

                totalSent += heartbeat.getDataSize();
            }
        }

        ++client;
    }
}

ClientID Server::AddClient(const sf::IpAddress& ip, const PortNumber& port)
{
    sf::Lock lock(mutex);
    for (auto& client : clients)
    {
        if (client.second.clientIp == ip && client.second.clientPort == port)
        {
            return ClientID(Network::NullID);
        }
    }

    ClientID id = lastId;
    ClientInfo info(ip, port, serverTime);
    clients.emplace(id, info);
    ++lastId;

    std::cout << "Client connected: " << ip << ":" << port << std::endl;

    return id;
}

ClientID Server::GetClientID(const sf::IpAddress& ip, const PortNumber& port)
{
    sf::Lock lock(mutex);
    for (auto& client : clients)
    {
        if (client.second.clientIp == ip && client.second.clientPort == port)
        {
            return client.first;
        }
    }

    return ClientID(Network::NullID);
}

bool Server::HasClient(const ClientID& id)
{
    return clients.find(id) != clients.end();
}

bool Server::HasClient(const sf::IpAddress& ip, const PortNumber& port)
{
    return GetClientID(ip, port) >= 0;
}

bool Server::GetClientInfo(const ClientID& id, ClientInfo& info)
{
    sf::Lock lock(mutex);
    for (auto& client : clients)
    {
        if (client.first == id)
        {
            info = client.second;

            return true;
        }
    }

    return false;
}

bool Server::RemoveClient(const ClientID& id)
{
    sf::Lock lock(mutex);
    auto client = clients.find(id);

    if (client == clients.end())
    {
        return false;
    }

    sf::Packet packet;
    StampPacket(PacketType::Disconnect, packet);
    Send(id, packet);
    clients.erase(client);

    return true;
}

bool Server::RemoveClient(const sf::IpAddress& ip, const PortNumber& port)
{
    sf::Lock lock(mutex);

    for (auto client = clients.begin(); client != clients.end(); ++client)
    {
        if (client->second.clientIp == ip && client->second.clientPort == port)
        {
            sf::Packet packet;
            StampPacket(PacketType::Disconnect, packet);
            Send(client->first, packet);
            clients.erase(client);

            return true;
        }
    }

    return false;
}

void Server::DisconnectAll()
{
    if (!running)
    {
        return;
    }

    sf::Packet packet;
    StampPacket(PacketType::Disconnect, packet);
    Broadcast(packet);
    sf::Lock lock(mutex);
    clients.clear();
}

bool Server::Start()
{
    if (running)
    {
        return false;
    }

    if (incoming.bind((unsigned short)Network::ServerPort) != sf::Socket::Done)
    {
        return false;
    }

    outgoing.bind(31337);
    Setup();

    std::cout << "Incoming port: " << incoming.getLocalPort() << " Outgoing port: " << outgoing.getLocalPort() << std::endl;
    listenThread.launch();
    running = true;

    return true;
}

bool Server::Stop()
{
    if (!running)
    {
        return false;
    }

    DisconnectAll();
    running = false;
    incoming.unbind();

    return true;
}

bool Server::IsRunning()
{
    return running;
}

unsigned int Server::GetClientCount()
{
    return clients.size();
}

std::string Server::GetClientList()
{
    std::string list;
    std::string delimiter = "--------------------------------------";
    list = delimiter;
    list += '\n';
    list += "ID";
    list += '\t';
    list += "Client IP:PORT";
    list += '\t'; list += '\t';
    list += "Ping";
    list += '\n';
    list += delimiter;
    list += '\n';

    for (auto client = clients.begin(); client != clients.end(); ++client) 
    {
        list += std::to_string(client->first);
        list += '\t';
        list += client->second.clientIp.toString() + ":" + std::to_string(client->second.clientPort);
        list += '\t';
        list += std::to_string(client->second.ping) + "ms.";
        list += '\n';
    }

    list += delimiter;
    list += '\n';
    list += "Total data sent: " + std::to_string(totalSent / 1000) + "kB. Total data received: " + std::to_string(totalReceived / 1000) + "kB";
    
    return list;
}

sf::Mutex& Server::GetMutex()
{
    return mutex;
}

void Server::Setup()
{
    lastId = 0;
    running = false;
    totalSent = 0;
    totalReceived = 0;
}
