#include "SnakeServerPCH.h"

SnakeServer::SnakeServer() :
mSnakeControlType(ESCT_Human)
{}

bool SnakeServer::HandleCollisionWithSnake(Snake* snake)
{
	if (snake == this) return false;

	// Check If Snake hit my tail
	for (const auto& tail : mTails)
	{
		if (snake->mPos == tail)
		{
//			DP2("-------Cof----------------")
//				DP2("From--Name:" << snake->mPlayerName << ", head:" << snake->mPos.first << "," << snake->mPos.second)
//				DP2("To--Name:" << this->mPlayerName << ", tail:" << tail.first << "," << tail.second)
//				DP2("-------------------------")
//				cout << "Does Wanto Die: " << snake->GetNetworkId() << std::endl;
			snake->SetDoesWantToDie(true);
			return true;
		}
	}
//	// Check If i have to die
//	for (const auto& tail : snake->mTails)
//	{
//		if (mPos == tail)
//		{
//			SetDoesWantToDie(true);
//			return true;
//		}
//	}

	return false;
}

void SnakeServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

void SnakeServer::Update()
{
	Snake::Update();

	pair<int,int>& oldPos= mPos;
	unsigned int oldTailLen = mTails.size();


	ClientProxyPtr client = NetworkManagerServer::sInstance->GetClientProxy(mPlayerID);
	if (client)
	{
		MoveList& moveList = client->GetUnprocessedMoveList();
		for (const Move& unprocessedMove : moveList)
		{
			if (this->isWantToDead)break;
			const InputState& currentState = unprocessedMove.GetInputState();
			float deltaTime = unprocessedMove.GetDeltaTime();
			SnakeMessage smsg(SnakeMessage::MESSAGE_TYPE::INPUT, currentState);
			this->AddMessage(smsg);
			SimulateMovement();
		}

		moveList.Clear();
	}

	if (oldPos != mPos)
	{
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ESRS_Pose);
	}
	if ( oldTailLen != mTails.size())
	{
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ESRS_TAIL);
		
	}
}

