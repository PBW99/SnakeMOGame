#pragma once

class Food : public GameObject
{
public:
	enum EFoodReplicationState
	{
		EFRS_Pose = 1 << 0,

		EFRS_AllState = EFRS_Pose
	};

	static const char kIcon = '*';

	virtual GO_TYPE GetGOType(){
		return GO_TYPE::FOOD;
	};

	virtual          ~Food() override;
	virtual bool HandleCollisionWithSnake(Snake* snake) override;

	virtual uint32_t GetAllStateMask() const override
	{
		return EFRS_AllState;
	}

	virtual void     Update() override;
	virtual void     Render() override;
	virtual uint32_t Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;
	virtual void     Read(InputMemoryBitStream&   inInputStream) override;
};

typedef shared_ptr<Food> FoodPtr;
