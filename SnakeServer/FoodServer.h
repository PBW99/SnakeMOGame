#pragma once

class FoodServer:public Food
{
public:
	static GameObjectPtr StaticCreate()
	{
		return NetworkManagerServer::sInstance->RegisterAndReturn(new FoodServer());
	}
	void HandleDying() override;
	virtual GO_TYPE GetGOType(){
		return GO_TYPE::FOOD;
	};
	virtual bool		HandleCollisionWithSnake(Snake* snake) override;

private:
	FoodServer();
};
