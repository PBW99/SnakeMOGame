#include "SnakeServerPCH.h"

void DebugPrint::PrintOM()
{
	cout << "OB size : " << ObjectManager::GetIns().mGameObjects.size() << "\n";
}

void DebugPrint::PrintNetMS()
{
	cout << "NetMS size : " << NetworkManagerServer::sInstance->mNetworkIdToGameObjectMap.size() << "\n";
}
