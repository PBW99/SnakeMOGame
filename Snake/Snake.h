#pragma once

class SnakeMessage
{
	friend class Snake;
public:

	enum class MESSAGE_TYPE
	{
		INPUT = 'INPT',
		ADD_TAIL = 'ATAI',
		NULLT = 'NULL'
	};

	MESSAGE_TYPE mType = MESSAGE_TYPE::NULLT;

	SnakeMessage(MESSAGE_TYPE mt);
	SnakeMessage(MESSAGE_TYPE mt, InputState inputState);

private:
	InputState mInputState;
};

class Snake : public GameObject
{
public:
	enum class DIRECTION
	{
		LEFT=0,
		RIGHT=1,
		UP=2,
		DOWN=3,
		NULLT=4
	};

	enum ESnakeReplicationState
	{
		ESRS_Pose = 1 << 0,
		ESRS_TAIL= 1 << 1,
		ESRS_Color = 1 << 2,
		ESRS_PlayerId = 1 << 3,
		ESRS_PlayerName= 1 << 4,

		ESRS_AllState = ESRS_Pose | ESRS_TAIL | ESRS_Color | ESRS_PlayerId |
		ESRS_PlayerName
	};

	static const char kHeadIcon = '#';
	static const char kTailIcon = '@';

	std::vector<std::pair<int, int>> mTails;
	CONSOLE_COLOR                    mColor;
	int                              mPlayerID;
	std::string                      mPlayerName;
	DIRECTION                        mDir = DIRECTION::LEFT;

	virtual ~Snake() override;

	virtual GO_TYPE GetGOType()
	{
		return GO_TYPE::SNAKE;
	};
	virtual void Update() override;
	virtual void Render() override;
	virtual bool HandleCollisionWithSnake(Snake* snake) override;

	virtual uint32_t GetAllStateMask() const override
	{
		return ESRS_AllState;
	}

	virtual Snake* GetAsSnake() override
	{
		return this;
	};
	virtual uint32_t Write(OutputMemoryBitStream& inOutputStream,
	                       uint32_t               inDirtyState) const override;
	virtual void Read(InputMemoryBitStream&       inInputStream) override;
	void         AddMessage(SnakeMessage          msg);

protected:
	std::queue<SnakeMessage> mMessages;
	void                     ProcessInput(const InputState& inputState);
	void                     ProcessAddTail();
	void                     SimulateMovement();
	void                     ProcessCollision();
	void                     ProcessCollisionWithWall();
};

typedef shared_ptr<Snake> SnakePtr;
