#include "SnakeServerPCH.h"

const int FoodManager::FOOD_SPAWN_NUM = WORLD_WIDTH * WORLD_HEIGHT / 15;
const int FoodManager::UPDATE_FRAME = 10;
int       FoodManager::mUpdateCnt = 0;

void FoodManager::Update()
{
	SpawnFood();
}

void FoodManager::SpawnFood()
{
	int           a = foodSize;
	GameObjectPtr go;

	for (; a < FOOD_SPAWN_NUM; a++)
	{
		int x;
		int y;

		x = a;
		y = a * a;


		do
		{
			x = UtilMath::GetRand(WORLD_WIDTH, y);
			y = UtilMath::GetRand(WORLD_HEIGHT, x);
			if (ObjectManager::GetIns().IsEmpty(x, y)) break;
		}
		while (1);

		go = GameObjectRegistry::sInstance->CreateGameObject(as_integer(GameObject::GO_TYPE::FOOD));
		go->mPos = std::make_pair(x, y);
//		NetworkManagerServer::sInstance->SetStateDirty(go->GetNetworkId(), Food::EFRS_Pose);
		foodSize++;
	}
}
