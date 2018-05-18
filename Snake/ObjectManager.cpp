#include "SnakePCH.h"

bool ObjectManager::IsEmpty(int x, int y)
{
	for (const auto& gameObject : mGameObjects)
	{
		if (gameObject->mPos.first == x && gameObject->mPos.second == y)
		{
			return false;
		}
	}
	return true;
}

void ObjectManager::Update()
{

//	for (const auto& go : mGameObjects)
	for (auto iter = mGameObjects.begin(); iter != mGameObjects.end();)
	{
		const auto& go = *iter;
		if (go->isWantToDead)
		{
			go->HandleDying();
			iter = mGameObjects.erase(iter);
			continue;
		}
		go->Update();
		++iter;
	}
}
