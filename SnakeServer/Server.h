#pragma once

class Server
{
private:
	Server();;
public:
	static Server& GetIns()
	{
		static Server server;
		return server;
	}

	bool InitNetworkManager();
	void Update();

	void     HandleNewClient(ClientProxyPtr  inClientProxy);
	void     HandleLostClient(ClientProxyPtr inClientProxy);
	SnakePtr GetSnakeForPlayer(int           inPlayerId);
	void     SpawnSnakeForPlayer(int         inPlayerId);
};
