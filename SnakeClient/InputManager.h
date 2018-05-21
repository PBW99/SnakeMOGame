#pragma once


class InputManager
{
private:
	InputManager();
	~InputManager();
public:
	static InputManager& GetIns()
	{
		static InputManager minputManager;
		return minputManager;
	}

	void        HandleInput();
	bool        IsTimeToSampleInput();
	bool        IsSomethingInputed();
	const Move& SampleInputAsMove();
	void        Update();

	MoveList& GetMoveList()
	{
		return mMoveList;
	}

private:
	MoveList    mMoveList;
	float       mNextTimeToSampleInput;
	const Move* mPendingMove;
	InputState  mCurState;
};
