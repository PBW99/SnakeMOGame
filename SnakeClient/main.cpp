#include "SnakeClientPCH.h"

char          g_szScreenBuffer[dfSCREEN_EXTRA_HEIGHT][dfSCREEN_EXTRA_WIDTH];
CONSOLE_COLOR g_szScreenBufferColor[dfSCREEN_EXTRA_HEIGHT][dfSCREEN_EXTRA_WIDTH
];
string g_destSocketStr;
string g_playerName;

int main(int argc, char* argv[])
{
	string playerName;
	cs_Initial();
	Buffer_Clear();


	//	cout << "서버 주소를 입력하세요\n:";
	//	cin >> g_destSocketStr;
	//	cout << "플레이어 이름을 입력하세요\n:";
	//	cin >> playerName;

	g_destSocketStr = argv[1];
	playerName      = argv[2];
	g_playerName    = playerName;

	Client::GetIns();
	try
	{
		while (1)
		{
			Client::GetIns().Update();
		}
	}
	catch (std::runtime_error e)
	{
		cout << "GameOver\n";
		Sleep(1000);
		getchar();
		exit(0);
	}
}
