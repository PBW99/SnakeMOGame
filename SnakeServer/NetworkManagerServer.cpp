#include "SnakeServerPCH.h"

NetworkManagerServer* NetworkManagerServer::sInstance;


NetworkManagerServer::NetworkManagerServer() :
	mNewPlayerId(1),
	mNewNetworkId(1),
	mTimeBetweenStatePackets(0.033f),
	mClientDisconnectTimeout(2.f)
{
}

bool NetworkManagerServer::StaticInit(uint16_t inPort)
{
	sInstance = new NetworkManagerServer();
	return sInstance->Init(inPort);
}

void NetworkManagerServer::HandleConnectionReset(const SocketAddress& inFromAddress)
{
	//just dc the client right away...
	auto it = mAddressToClientMap.find(inFromAddress);
	if (it != mAddressToClientMap.end())
	{
		HandleClientDisconnected(it->second);
	}
}

void NetworkManagerServer::ProcessPacket(InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress)
{
	//try to get the client proxy for this address
	//pass this to the client proxy to process
	// Check Client Proxy From Address
	auto it = mAddressToClientMap.find(inFromAddress);
	if (it == mAddressToClientMap.end())
	{
		//didn't find one? it's a new cilent..is the a HELO? if so, create a client proxy...
		HandlePacketFromNewClient(inInputStream, inFromAddress);
	}
	else
	{
		ProcessPacket((*it).second, inInputStream);
	}
}


void NetworkManagerServer::ProcessPacket(ClientProxyPtr inClientProxy, InputMemoryBitStream& inInputStream)
{
	//Remember we got a packet so we know not to disconnect for a bit
	inClientProxy->UpdateLastPacketTime();

	// Read the PacketType
	uint32_t packetType;
	inInputStream.Read(packetType);

	switch (packetType)
	{
	case kHelloCC:
		// Not Deleted Address came
		//need to resend welcome. to be extra safe we should check the name is the one we expect from this address,
		//otherwise something weird is going on...
		SendWelcomePacket(inClientProxy);
		break;
	case kInputCC:
		HandleInputPacket(inClientProxy, inInputStream);
		break;
	default:
		LOG( "Unknown packet type received from %s", inClientProxy->GetSocketAddress().ToString().c_str() );
		break;
	}
}


void NetworkManagerServer::HandlePacketFromNewClient(InputMemoryBitStream& inInputStream,
													 const SocketAddress&  inFromAddress)
{
	//Read PacketType- is it a hello?
	uint32_t packetType;
	inInputStream.Read(packetType);
	if (packetType == kHelloCC)
	{
		//Read the name
		string name;
		inInputStream.Read(name);

		// Create Client Proxy
		ClientProxyPtr newClientProxy = std::make_shared<ClientProxy>(inFromAddress, name, mNewPlayerId++);
		mAddressToClientMap[inFromAddress] = newClientProxy;
		mPlayerIdToClientMap[newClientProxy->GetPlayerId()] = newClientProxy;

		//Tell the server about this client, spawn a Snake, etc...
		//if we had a generic message system, this would be a good use for it...
		//instead we'll just tell the server directly
		Server::GetIns().HandleNewClient(newClientProxy);

		//Welcome the client...
		SendWelcomePacket(newClientProxy);

		//Init the replication manager with everything we know about!
		for (const auto& pair : mNetworkIdToGameObjectMap)
		{
			newClientProxy->GetReplicationManagerServer().ReplicateCreate(pair.first, pair.second->GetAllStateMask());
		}
	}
	else
	{
		//bad incoming packet from unknown client- we're under attack!!
		LOG( "Bad incoming packet from unknown client at socket %s", inFromAddress.ToString().c_str() );
	}
}

void NetworkManagerServer::SendWelcomePacket(ClientProxyPtr inClientProxy)
{
	OutputMemoryBitStream welcomePacket;

	welcomePacket.Write(kWelcomeCC);
	welcomePacket.Write(inClientProxy->GetPlayerId());

	LOG( "Server Welcoming, new client '%s' as player %d", inClientProxy->GetName().c_str(), inClientProxy->GetPlayerId()
	);

	SendPacket(welcomePacket, inClientProxy->GetSocketAddress());
}


void NetworkManagerServer::SendOutgoingPackets()
{
	//let's send a client a state packet whenever their move has come in...
	for (auto it = mAddressToClientMap.begin(), end = mAddressToClientMap.end(); it != end; ++it)
	{
		ClientProxyPtr& clientProxy = it->second;
		if (clientProxy->IsLastMoveTimestampDirty())
		{
			SendStatePacketToClient(clientProxy);
		}
	}
}


void NetworkManagerServer::SendStatePacketToClient(ClientProxyPtr inClientProxy)
{
	//build state packet
	OutputMemoryBitStream statePacket;

	//it's state!
	statePacket.Write(kStateCC);

	WriteLastMoveTimestampIfDirty(statePacket, inClientProxy);

	AddScoreBoardStateToPacket(statePacket);

	inClientProxy->GetReplicationManagerServer().Write(statePacket);
	DP("Sent byte Len!! : " << statePacket.GetByteLength());
	SendPacket(statePacket, inClientProxy->GetSocketAddress());
}

void NetworkManagerServer::WriteLastMoveTimestampIfDirty(OutputMemoryBitStream& inOutputStream,
														 ClientProxyPtr         inClientProxy)
{
	//first, dirty?
	bool isTimestampDirty = inClientProxy->IsLastMoveTimestampDirty();
	inOutputStream.Write(isTimestampDirty);
	DP("Send TS Dirty" << isTimestampDirty)
	if (isTimestampDirty)
	{
		inOutputStream.Write(inClientProxy->GetUnprocessedMoveList().GetLastMoveTimestamp());
		inClientProxy->SetIsLastMoveTimestampDirty(false);
	}
}


void NetworkManagerServer::AddScoreBoardStateToPacket(OutputMemoryBitStream& inOutputStream)
{
	ScoreBoardManager::sInstance->Write(inOutputStream);
}


int NetworkManagerServer::GetNewNetworkId()
{
	int toRet = mNewNetworkId++;
	if (mNewNetworkId < toRet)
	{
		LOG( "Network ID Wrap Around!!! You've been playing way too long...", 0 );
	}

	return toRet;
}

void NetworkManagerServer::HandleInputPacket(ClientProxyPtr inClientProxy, InputMemoryBitStream& inInputStream)
{
	uint32_t moveCount = 0;
	Move     move;
	// Read MoveCount
	inInputStream.Read(moveCount, 2);
	DP("Handler Input")

	for (; moveCount > 0; --moveCount)
	{
		if (move.Read(inInputStream))
		{
			if (inClientProxy->GetUnprocessedMoveList().AddMove(move))
			{
				inClientProxy->SetIsLastMoveTimestampDirty(true);
			}
		}
	}
}

ClientProxyPtr NetworkManagerServer::GetClientProxy(int inPlayerId) const
{
	auto it = mPlayerIdToClientMap.find(inPlayerId);
	if (it != mPlayerIdToClientMap.end())
	{
		return it->second;
	}

	return nullptr;
}

void NetworkManagerServer::CheckForDisconnects()
{
	vector<ClientProxyPtr> clientsToDC;

	float            minAllowedLastPacketFromClientTime = Timing::sInstance.GetTimef() - mClientDisconnectTimeout;
	for (const auto& pair : mAddressToClientMap)
	{
		if (pair.second->GetLastPacketFromClientTime() < minAllowedLastPacketFromClientTime)
		{
			//can't remove from map while in iterator, so just remember for later...
			clientsToDC.push_back(pair.second);
		}
	}

	for (ClientProxyPtr client : clientsToDC)
	{
		HandleClientDisconnected(client);
	}
}

void NetworkManagerServer::HandleClientDisconnected(ClientProxyPtr inClientProxy)
{
	mPlayerIdToClientMap.erase(inClientProxy->GetPlayerId());
	mAddressToClientMap.erase(inClientProxy->GetSocketAddress());

	// Notify Server Disconnection
	Server::GetIns().HandleLostClient(inClientProxy);

	//was that the last client? if so, bye!
	if (mAddressToClientMap.empty())
	{
		//Don't Turn off Server
//		Engine::sInstance->SetShouldKeepRunning(false);
	}
}

void NetworkManagerServer::RegisterGameObject(GameObjectPtr inGameObject)
{
	//assign network id
	int newNetworkId = GetNewNetworkId();
	inGameObject->SetNetworkId(newNetworkId);

	//add mapping from network id to game object
	mNetworkIdToGameObjectMap[newNetworkId] = inGameObject;

	//tell all client proxies this is new...
	for (const auto& pair : mAddressToClientMap)
	{
		pair.second->GetReplicationManagerServer().ReplicateCreate(newNetworkId, inGameObject->GetAllStateMask());
	}
}


void NetworkManagerServer::UnregisterGameObject(GameObject* inGameObject)
{
	int networkId = inGameObject->GetNetworkId();
	mNetworkIdToGameObjectMap.erase(networkId);

	//tell all client proxies to STOP replicating!
	//tell all client proxies this is new...
	for (const auto& pair : mAddressToClientMap)
	{
		pair.second->GetReplicationManagerServer().ReplicateDestroy(networkId);
	}
}

void NetworkManagerServer::SetStateDirty(int inNetworkId, uint32_t inDirtyState)
{
	//tell everybody this is dirty
	for (const auto& pair : mAddressToClientMap)
	{
		pair.second->GetReplicationManagerServer().SetStateDirty(inNetworkId, inDirtyState);
	}
}
