#include "SnakePCH.h"


// 화면 버퍼를 지워주는 함수
//
// 매 프레임 그림을 그리기 직전에 버퍼를 지워 준다. 
// 안그러면 이전 프레임의 잔상이 남으니까
//--------------------------------------------------------------------
void Buffer_Clear(void)
{
	int iCnt;
	int jCnt;
	for (iCnt = 0; iCnt < dfSCREEN_EXTRA_HEIGHT; iCnt++)
	{
		memset(g_szScreenBuffer[iCnt], ' ', dfSCREEN_EXTRA_WIDTH);
		for (jCnt = 0; jCnt < dfSCREEN_EXTRA_WIDTH; jCnt++)
		{
			g_szScreenBufferColor[iCnt][jCnt] = CONSOLE_COLOR::DEFAULT;
		}
		g_szScreenBuffer[iCnt][dfSCREEN_EXTRA_WIDTH - 1] = '\0';
	}
}

//--------------------------------------------------------------------
// 버퍼의 특정 위치에 원하는 문자를 출력.
//
// 입력 받은 X,Y 좌표에 아스키코드 하나를 출력한다. (버퍼에 그림)
//--------------------------------------------------------------------
void Sprite_Draw(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
		return;

	g_szScreenBuffer[iY][iX] = chSprite;
	g_szScreenBufferColor[iY][iX] = CONSOLE_COLOR::DEFAULT;
}

void Sprite_Draw(int iX, int iY, CONSOLE_COLOR color, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_WIDTH - 1 || iY >= dfSCREEN_HEIGHT)
		return;

	g_szScreenBuffer[iY][iX] = chSprite;
	g_szScreenBufferColor[iY][iX] = color;
}

//--------------------------------------------------------------------
// 버퍼의 특정 위치에 원하는 문자를 출력.
//
// 입력 받은 X,Y 좌표에 아스키코드 하나를 출력한다. (버퍼에 그림)
//--------------------------------------------------------------------
void Sprite_Extra_Draw(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_EXTRA_WIDTH - 1 || iY >= dfSCREEN_EXTRA_HEIGHT)
		return;

	g_szScreenBuffer[iY][iX] = chSprite;
	g_szScreenBufferColor[iY][iX] = CONSOLE_COLOR::DEFAULT;
}

void Sprite_Extra_Draw(int iX, int iY, CONSOLE_COLOR color, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= dfSCREEN_EXTRA_WIDTH - 1 || iY >= dfSCREEN_EXTRA_HEIGHT)
		return;

	g_szScreenBuffer[iY][iX] = chSprite;
	g_szScreenBufferColor[iY][iX] = color;
}

//--------------------------------------------------------------------
// 버퍼의 내용을 화면으로 찍어주는 함수.
//
// 적군,아군,총알 등을 g_szScreenBuffer 에 넣어주고, 
// 1 프레임이 끝나는 마지막에 본 함수를 호출하여 버퍼 -> 화면 으로 그린다.
//--------------------------------------------------------------------


void Buffer_Flip(void)
{
	int iCnt;
	int jCnt;
	for (iCnt = 0; iCnt < dfSCREEN_EXTRA_HEIGHT; iCnt++)
	{
		cs_MoveCursor(0, iCnt);
		printf(g_szScreenBuffer[iCnt]);
		for (jCnt = 0; jCnt < dfSCREEN_EXTRA_WIDTH; jCnt++)
		{
			if (g_szScreenBufferColor[iCnt][jCnt] != CONSOLE_COLOR::DEFAULT)
			{
				cs_SetColor(g_szScreenBufferColor[iCnt][jCnt]);
				cs_MoveCursor(jCnt, iCnt);
				printf("%c", g_szScreenBuffer[iCnt][jCnt]);
			}
		}
		cs_SetColor(CONSOLE_COLOR::DEFAULT);
	}
}
