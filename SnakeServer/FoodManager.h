#pragma once
#include "World.h"
#include "UtilMath.h"
#include "Food.h"

class FoodManager
{
private:
	FoodManager(){};

	static const int FOOD_SPAWN_NUM;

public:
	static FoodManager& GetIns()
	{
		static FoodManager foodManager;
		return foodManager;
	};
	
	void Update();
	void SpawnFood();
	

	static const int UPDATE_FRAME;
	static int mUpdateCnt;
	int foodSize=0;
};
