#pragma once
enum ESnakeControlType
{
	ESCT_Human,
	ESCT_AI
};

class SnakeServer : public Snake
{
public:
	static GameObjectPtr StaticCreate()
	{
		return NetworkManagerServer::sInstance->RegisterAndReturn(new SnakeServer());
	}
	virtual bool HandleCollisionWithSnake(Snake* snake) override;
	virtual void HandleDying() override;

	virtual void Update() override;

	virtual GO_TYPE GetGOType(){
		return GO_TYPE::SNAKE;
	};

	void SetSnakeControlType(ESnakeControlType inSnakeControlType) {
		mSnakeControlType = inSnakeControlType;
	}


private:
	SnakeServer();
	ESnakeControlType	mSnakeControlType;


	
};
