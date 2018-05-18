#pragma once

class Client
{
private:
	Client();;
public:
	static Client& GetIns()
	{
		static Client client;
		return client;
	}
	void Update();
	
};

