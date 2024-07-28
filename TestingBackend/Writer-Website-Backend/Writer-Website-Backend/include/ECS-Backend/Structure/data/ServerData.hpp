#ifndef SERVER_DATA_HPP
#define SERVER_DATA_HPP

#include <ECS-Backend/Keywords.hpp>

enum ServerState
{
	Activated,
	Terminated
};

enum ServerEvents
{
	SE_Terminate,
	SE_NULL
};

struct ServerData
{
	ServerState                   state;
	std::array<ServerEvents, 100> events; // Handles events, may need to reconfigure

};

#endif // !SERVER_DATA_HPP
