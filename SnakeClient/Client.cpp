#include "SnakeClientPCH.h"

Client::Client()
{
	SocketUtil::StaticInit();
	GameObjectRegistry::StaticInit();
	RenderManager::GetIns();
	Context::GetIns();
	World::GetIns();

	GameObjectRegistry::sInstance->RegisterCreationFunction(
		as_integer(GameObject::GO_TYPE::SNAKE), SnakeClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction(
		as_integer(GameObject::GO_TYPE::FOOD), FoodClient::StaticCreate);

	SocketAddressPtr serverAddress = SocketAddressFactory::CreateIPv4FromString(g_destSocketStr);

	NetworkManagerClient::StaticInit(*serverAddress, g_playerName);
	NetworkManagerClient::sInstance->SetSimulatedLatency(0.0f);
}

void Client::Update()
{
	Timing::sInstance.Update();

	NetworkManagerClient::sInstance->ProcessIncomingPackets();

	InputManager::GetIns().Update();

	if (World::GetIns().mPlayer != nullptr)
	{

		ObjectManager::GetIns().Update();
		RenderManager::GetIns().Update();
	}

	NetworkManagerClient::sInstance->SendOutgoingPackets();
}
