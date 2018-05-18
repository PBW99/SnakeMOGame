#include "SnakeClientPCH.h"


namespace
{
	float kTimeBetweenInputSamples = 0.01f;
}

void InputManager::HandleInput()
{
	mCurState.mLeftKey  = false;
	mCurState.mRightKey = false;
	mCurState.mUpKey    = false;
	mCurState.mDownKey  = false;

	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		mCurState.mLeftKey = true;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		mCurState.mRightKey = true;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		mCurState.mUpKey = true;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		mCurState.mDownKey = true;
	}
}


const Move& InputManager::SampleInputAsMove()
{
	return mMoveList.AddMove(mCurState, Timing::sInstance.GetFrameStartTime());
}

bool InputManager::IsTimeToSampleInput()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if (time > mNextTimeToSampleInput)
	{
		mNextTimeToSampleInput = mNextTimeToSampleInput + kTimeBetweenInputSamples;
		return true;
	}

	return false;
}

bool InputManager::IsSomethingInputed()
{
	if (mCurState.mLeftKey == false && mCurState.mRightKey == false && mCurState.
		mUpKey == false && mCurState.mDownKey == false)
	{
		return false;
	}
	return true;
}

void InputManager::Update()
{
	HandleInput();
//	if (IsTimeToSampleInput() &&  IsSomethingInputed())
	if (IsTimeToSampleInput() )
	{
		mPendingMove = &SampleInputAsMove();
	}
}
