#pragma once

class SnakeClient : public Snake
{
public:
	static GameObjectPtr StaticCreate()
	{
		return GameObjectPtr(new SnakeClient());
	}
	virtual void Render() override;
	virtual void HandleDying() override;
};

