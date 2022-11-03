#ifndef NETWORK_DEFINITIONS_H
#define NETWORK_DEFINITIONS_H

enum class Network
{
	HighestTimestamp = 2147483647,
	ClientTimeout = 10000,
	ServerPort = 5600,
	NullID = -1
};

using ClientID = int;
using PortNumber = unsigned short;

#endif
