#pragma once

class ObjectManager
{
private:
	ObjectManager(){};
public:
	static ObjectManager& GetIns()
	{
		static ObjectManager objectManager;
		return objectManager;
	}
	std::deque<GameObjectPtr> mGameObjects;
	bool IsEmpty(int x, int y);
	void Update();
	
};
