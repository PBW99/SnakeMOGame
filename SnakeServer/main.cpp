#include "SnakeServerPCH.h"

char g_szScreenBuffer[dfSCREEN_EXTRA_HEIGHT][dfSCREEN_EXTRA_WIDTH];
CONSOLE_COLOR g_szScreenBufferColor[dfSCREEN_EXTRA_HEIGHT][dfSCREEN_EXTRA_WIDTH];
char** __argv;
int __argc;

int main(int argc, char* argv[])
{
	__argc = argc;
	__argv = argv;
	Server::GetIns();
	while (1)
	{
		Server::GetIns().Update();
	}
}
