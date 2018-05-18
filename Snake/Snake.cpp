#include "SnakePCH.h"

using namespace std;


SnakeMessage::SnakeMessage(MESSAGE_TYPE mt): mType(mt),
											 mInputState()
{
}

SnakeMessage::SnakeMessage(MESSAGE_TYPE mt, InputState inputState) : mType(mt),
																	 mInputState(inputState)
{
}


Snake::~Snake()
{
}

void Snake::Update()
{
}


void Snake::Render()
{

}


void Snake::AddMessage(SnakeMessage msg)
{
	this->mMessages.push(msg);
}

bool Snake::HandleCollisionWithSnake(Snake* snake)
{
	return false;
}

uint32_t Snake::Write(OutputMemoryBitStream& inOutputStream,
					  uint32_t               inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & ESRS_Pose)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(mPos.first);
		inOutputStream.Write(mPos.second);

		writtenState |= ESRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & ESRS_TAIL)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(mTails);

		writtenState |= ESRS_TAIL;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & ESRS_Color)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(mColor);

		writtenState |= ESRS_Color;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}


	if (inDirtyState & ESRS_PlayerId)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(mPlayerID);

		writtenState |= ESRS_PlayerId;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & ESRS_PlayerName)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(mPlayerName);

		writtenState |= ESRS_PlayerName;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}
	return 0;
}

void Snake::Read(InputMemoryBitStream& inInputStream)
{
	bool stateBit;

	uint32_t readState = 0;

	inInputStream.Read(stateBit);

	if (stateBit)
	{
		inInputStream.Read(mPos.first);
		inInputStream.Read(mPos.second);

		readState |= ESRS_Pose;
	}

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		inInputStream.Read(mTails);

		readState |= ESRS_TAIL;
	}


	inInputStream.Read(stateBit);
	if (stateBit)
	{
		inInputStream.Read(mColor);

		readState |= ESRS_Color;
	}


	inInputStream.Read(stateBit);
	if (stateBit)
	{
		inInputStream.Read(mPlayerID);

		readState |= ESRS_PlayerId;
	}

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		inInputStream.Read(mPlayerName);

		readState |= ESRS_PlayerName;
	}

	return;
}

void Snake::ProcessInput(const InputState& inputState)
{
	float xDelta = inputState.mDesiredHorizontal;
	float yDelta = inputState.mDesiredVertical;

	if (xDelta > 0) this->mDir = Snake::DIRECTION::LEFT;
	if (xDelta < 0) this->mDir = Snake::DIRECTION::RIGHT;
	if (yDelta > 0) this->mDir = Snake::DIRECTION::UP;
	if (yDelta < 0) this->mDir = Snake::DIRECTION::DOWN;
}

void Snake::ProcessAddTail()
{
	// Add tail brute force
	switch (mDir)
	{
	case DIRECTION::LEFT:
		mTails.push_back(make_pair(mPos.first + 1, mPos.second));
		break;
	case DIRECTION::RIGHT:
		mTails.push_back(make_pair(mPos.first - 1, mPos.second));
		break;
	case DIRECTION::UP:
		mTails.push_back(make_pair(mPos.first, mPos.second + 1));
		break;
	case DIRECTION::DOWN:
		mTails.push_back(make_pair(mPos.first, mPos.second - 1));
		break;
	case DIRECTION::NULLT:
		break;
	}
}

void Snake::SimulateMovement()
{
	// Do task in queue
	while (mMessages.size() > 0)
	{
		const auto& msg = mMessages.front();
		if (msg.mType == SnakeMessage::MESSAGE_TYPE::INPUT)
		{
			ProcessInput(msg.mInputState);
		}
		if (msg.mType == SnakeMessage::MESSAGE_TYPE::ADD_TAIL)
		{
			ProcessAddTail();
		}
		mMessages.pop();
	}

	// Move Tail
	int a;
	for (a = mTails.size() - 1; a >= 1; --a)
	{
		mTails[a].first  = mTails[a - 1].first;
		mTails[a].second = mTails[a - 1].second;
	}

	if (mTails.size() > 0)
	{
		mTails[a].first  = mPos.first;
		mTails[a].second = mPos.second;
	}

	// Move Head
	switch (mDir)
	{
	case DIRECTION::LEFT:
		mPos.first--;
		break;
	case DIRECTION::RIGHT:
		mPos.first++;
		break;
	case DIRECTION::UP:
		mPos.second--;
		break;
	case DIRECTION::DOWN:
		mPos.second++;
		break;
	case DIRECTION::NULLT:
		break;
	}

	ProcessCollision();
	ProcessCollisionWithWall();
}

void Snake::ProcessCollision()
{
	for (const auto& go : ObjectManager::GetIns().mGameObjects)
	{
		if (go->HandleCollisionWithSnake(this))
		{
		}
	}
}

void Snake::ProcessCollisionWithWall()
{
	if (mPos.first < 0)
		mPos.first = 0;
	if (mPos.first > WORLD_WIDTH - 1)
		mPos.first = WORLD_WIDTH - 1;
	if (mPos.second < 0)
		mPos.second = 0;
	if (mPos.second > WORLD_HEIGHT - 1)
		mPos.second = WORLD_HEIGHT - 1;
}
