#ifndef SERVER_SYSTEM_UPDATE_HPP
#define SERVER_SYSTEM_UPDATE_HPP

#include <ECS-Backend/Keywords.hpp>
#include <ECS-Backend/Structure/data/ServerData.hpp>

flecs::entity ServerEventInitalize(flecs::world& world)
{
	auto dataEntity = world.entity();
	dataEntity.add<ServerData>();

	auto dataEntity_c = dataEntity.get_mut<ServerData>();
	dataEntity_c->state = ServerState::Activated;
	for (Int16 i = 0; i < dataEntity_c->events.size(); i++)
	{
		dataEntity_c->events[i] = ServerEvents::SE_NULL;
	}
	std::cout << "Server data... Loaded." << std::endl;

	return dataEntity;
}

void ServerEventSend(flecs::world& _World, flecs::entity& dataEntity, ServerEvents ServerEvent)
{
	auto dataEntity_c = dataEntity.get_mut<ServerData>();
	for (Int16 i = 0; i < dataEntity_c->events.size(); i++)
	{
		if (dataEntity_c->events[i] == ServerEvents::SE_NULL)
		{
			dataEntity_c->events[i] = ServerEvent;
			break;
		}
	}
}

void ServerEventProcess(ServerEvents ServerEvent, flecs::entity& dataEntity)
{
	if (ServerEvent == ServerEvents::SE_Terminate)
	{
		auto dataEntity_c = dataEntity.get_mut<ServerData>();
		dataEntity_c->state = ServerState::Terminated;
	}
}

void ServerEventUpdate(flecs::world& _World, flecs::entity& dataEntity)
{
	auto dataEntity_c = dataEntity.get_mut<ServerData>();
	for (Int16 i = 0; i < dataEntity_c->events.size(); i++)
	{
		if (dataEntity_c->events[i] != ServerEvents::SE_NULL && i == 0)
		{
			ServerEventProcess(dataEntity_c->events[i], dataEntity);
			dataEntity_c->events[i] = ServerEvents::SE_NULL;
			break;
		}
		else if (dataEntity_c->events[i] == ServerEvents::SE_NULL)
		{
			ServerEventProcess(dataEntity_c->events[i], dataEntity);
			dataEntity_c->events[i] = ServerEvents::SE_NULL;
			for (Int16 ii = 0; ii < i; ii++)
			{
				dataEntity_c->events[ii] = ServerEvents::SE_NULL;
			}
			break;
		}
	}
}

#endif // !SERVER_SYSTEM_UPDATE_HPP
