#pragma once

class Snake;

class GameObject
{
	friend class ObjectManager;
private:
	int  mNetworkId = 0;
public:
	enum class GO_TYPE
	{
		SNAKE = 'SNAK',
		FOOD = 'FOOD'
	};



	virtual ~GameObject() = default;
	virtual GO_TYPE GetGOType() = 0;
	void SetPos(int x, int y);

	int GetNetworkId() const
	{
		return mNetworkId;
	}

	void         SetNetworkId(int      inNetworkId);
	void         SetDoesWantToDie(bool tf);
	virtual void Update(){};
	virtual void Render(){};
	virtual void HandleDying(){};

	virtual bool HandleCollisionWithSnake(Snake* snake)
	{
		return false;
	};

	virtual Snake* GetAsSnake()
	{
		return nullptr;
	};

	virtual uint32_t GetAllStateMask() const
	{
		return 0;
	}


	virtual uint32_t Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
	{
		(void)inOutputStream;
		(void)inDirtyState;
		return 0;
	}

	virtual void Read(InputMemoryBitStream& inInputStream)
	{
		(void)inInputStream;
	}

	bool isWantToDead = false;
	std::pair<int, int> mPos;
};

typedef shared_ptr<GameObject> GameObjectPtr;
