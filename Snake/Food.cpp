#include "SnakePCH.h"


bool Food::HandleCollisionWithSnake(Snake* snake)
{


	return false;
}

void Food::Update()
{
}

void Food::Render()
{
}

Food::~Food()
{
}

uint32_t Food::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & EFRS_Pose)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(mPos.first);
		inOutputStream.Write(mPos.second);

		writtenState |= EFRS_Pose;
	}
	
	return 0;
}


void Food::Read(InputMemoryBitStream& inInputStream)
{
	bool stateBit;

	uint32_t readState = 0;

	inInputStream.Read(stateBit);

	if (stateBit)
	{

		inInputStream.Read(mPos.first);
		inInputStream.Read(mPos.second);

		readState |= EFRS_Pose;
	}

	return;

}
