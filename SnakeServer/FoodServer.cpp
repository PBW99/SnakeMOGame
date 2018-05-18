#include "SnakeServerPCH.h"


FoodServer::FoodServer()
{
}

void FoodServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


bool FoodServer::HandleCollisionWithSnake(Snake* snake)
{
	if (snake->mPos == this->mPos)
	{

		SetDoesWantToDie(true);
		FoodManager::GetIns().foodSize--;

		SnakeMessage smsg(SnakeMessage::MESSAGE_TYPE::ADD_TAIL);
		snake->AddMessage(smsg);
		ScoreBoardManager::sInstance->IncScore(snake->mPlayerID, 1);

		return true;
	}
	return false;
}

