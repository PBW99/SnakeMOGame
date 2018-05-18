#pragma once

#define dfSCREEN_WIDTH 81
#define dfSCREEN_HEIGHT 24
#define dfSCREEN_EXTRA_WIDTH 93
#define dfSCREEN_EXTRA_HEIGHT 24

#define dfCOLOR_NUM 3

#define WORLD_WIDTH 160
#define WORLD_HEIGHT 60

extern char g_szScreenBuffer[dfSCREEN_EXTRA_HEIGHT][dfSCREEN_EXTRA_WIDTH];
extern CONSOLE_COLOR g_szScreenBufferColor[dfSCREEN_EXTRA_HEIGHT][dfSCREEN_EXTRA_WIDTH];

class World
{
private:
	World()
	{
	};
public:

	static World& GetIns()
	{
		static World world;
		return world;
	}

	SnakePtr mPlayer;
};
