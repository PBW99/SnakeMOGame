#include "SnakeServerPCH.h"

Server::Server()
{
	SocketUtil::StaticInit();
	GameObjectRegistry::StaticInit();
	Context::GetIns();
	World::GetIns();

	GameObjectRegistry::sInstance->RegisterCreationFunction(
		as_integer(GameObject::GO_TYPE::SNAKE), SnakeServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction(
		as_integer(GameObject::GO_TYPE::FOOD), FoodServer::StaticCreate);
	InitNetworkManager();
	FoodManager::GetIns();
}

bool Server::InitNetworkManager()
{
	string   portString = StringUtils::GetCommandLineArg(1);
	uint16_t port = stoi(portString);

	return NetworkManagerServer::StaticInit(port);
}

void Server::Update()
{
	Timing::sInstance.Update();

	NetworkManagerServer::sInstance->ProcessIncomingPackets();

	NetworkManagerServer::sInstance->CheckForDisconnects();

	ObjectManager::GetIns().Update();

	if (FoodManager::GetIns().mUpdateCnt % FoodManager::UPDATE_FRAME == 0)
	{
		FoodManager::GetIns().Update();
	}
	FoodManager::GetIns().mUpdateCnt += 1;

	NetworkManagerServer::sInstance->SendOutgoingPackets();
	PRINT_OM()
	PRINT_NetMS()
}


void Server::HandleNewClient(ClientProxyPtr inClientProxy)
{
	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->AddEntry(playerId, inClientProxy->GetName());
	SpawnSnakeForPlayer(playerId);
}

void Server::SpawnSnakeForPlayer(int inPlayerId)
{
	SnakePtr snake = std::static_pointer_cast<Snake>(
		GameObjectRegistry::sInstance->CreateGameObject(as_integer(GameObject::GO_TYPE::SNAKE)));
	snake->mColor = ScoreBoardManager::sInstance->GetEntry(inPlayerId)->GetColor();
	snake->mPlayerName = NetworkManagerServer::sInstance->GetClientProxy(inPlayerId)->GetName();
	snake->mPlayerID = inPlayerId;
	//gotta pick a random spawn location than this...
	snake->mPos = make_pair(UtilMath::GetRand(WORLD_WIDTH, inPlayerId), UtilMath::GetRand(WORLD_HEIGHT, inPlayerId));
	int rand4 = UtilMath::GetRand(4, inPlayerId);
	int* direction = (int*)&snake->mDir;
	*direction = rand4;
}

void Server::HandleLostClient(ClientProxyPtr inClientProxy)
{
	//kill client's snake
	//remove client from scoreboard
	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->RemoveEntry(playerId);
	SnakePtr snake = GetSnakeForPlayer(playerId);
	if (snake)
	{
		snake->SetDoesWantToDie(true);
	}
}

SnakePtr Server::GetSnakeForPlayer(int inPlayerId)
{
	//run through the objects till we find the snake...
	//it would be nice if we kept a pointer to the snake on the clientproxy
	//but then we'd have to clean it up when the snake died, etc.
	//this will work for now until it's a perf issue
	const auto& gameObjects = ObjectManager::GetIns().mGameObjects;
	for (int    i = 0, c = gameObjects.size(); i < c; ++i)
	{
		GameObjectPtr go = gameObjects[i];
		Snake*        snake = go->GetAsSnake();
		if (snake && snake->mPlayerID == inPlayerId)
		{
			return std::static_pointer_cast<Snake>(go);
		}
	}

	return nullptr;
}
