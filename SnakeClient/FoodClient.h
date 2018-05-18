#pragma once

class FoodClient : public Food
{
public:
	static GameObjectPtr StaticCreate()
	{
		return GameObjectPtr(new FoodClient());
	}
	virtual void Render() override;

	
};

