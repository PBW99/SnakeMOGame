#include "SnakePCH.h"


// ȭ�� ���۸� �����ִ� �Լ�
//
// �� ������ �׸��� �׸��� ������ ���۸� ���� �ش�. 
// �ȱ׷��� ���� �������� �ܻ��� �����ϱ�
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
// ������ Ư�� ��ġ�� ���ϴ� ���ڸ� ���.
//
// �Է� ���� X,Y ��ǥ�� �ƽ�Ű�ڵ� �ϳ��� ����Ѵ�. (���ۿ� �׸�)
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
// ������ Ư�� ��ġ�� ���ϴ� ���ڸ� ���.
//
// �Է� ���� X,Y ��ǥ�� �ƽ�Ű�ڵ� �ϳ��� ����Ѵ�. (���ۿ� �׸�)
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
// ������ ������ ȭ������ ����ִ� �Լ�.
//
// ����,�Ʊ�,�Ѿ� ���� g_szScreenBuffer �� �־��ְ�, 
// 1 �������� ������ �������� �� �Լ��� ȣ���Ͽ� ���� -> ȭ�� ���� �׸���.
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

