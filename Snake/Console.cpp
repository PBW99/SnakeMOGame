#include "SnakePCH.h"

HANDLE hConsole;

//-------------------------------------------------------------
// �̷��� ���ϴ�.
//
// #incude <stdio.h>
// #include <windows.h>
// #incude "Console.h"
//
// void main(void)
// {
//		cs_Initial();
//
//		cs_MoveCursor(0, 0);	// Ŀ���� 0, 0 ��ġ��
//		printf("abcde");		// 0, 0 ��ġ�� �۾��� ����
//		cs_MoveCursor(20, 10);	// Ŀ���� 20, 10 ��ġ��
//		printf("abcde");		// 0, 0 ��ġ�� �۾��� ����
//
// }
//-------------------------------------------------------------

//-------------------------------------------------------------
// �ܼ� ��� ���� �غ� �۾�.
//
//-------------------------------------------------------------
void cs_Initial(void)
{
	CONSOLE_CURSOR_INFO stConsoleCursor;

	//-------------------------------------------------------------
	// ȭ���� Ŀ���� �Ⱥ��̰Բ� �����Ѵ�.
	//-------------------------------------------------------------
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1; // Ŀ�� ũ��.
	// �̻��ϰԵ� 0 �̸� ���´�. 1���ϸ� �ȳ��´�.

	//-------------------------------------------------------------
	// �ܼ�ȭ�� (���ٴٵ� �ƿ�ǲ) �ڵ��� ���Ѵ�.
	//-------------------------------------------------------------
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hConsole, &stConsoleCursor);
}

//-------------------------------------------------------------
// �ܼ� ȭ���� Ŀ���� X, Y ��ǥ�� �̵���Ų��.
//
//-------------------------------------------------------------
void cs_MoveCursor(int iPosX, int iPosY)
{
	COORD stCoord;
	stCoord.X = iPosX;
	stCoord.Y = iPosY;
	//-------------------------------------------------------------
	// ���ϴ� ��ġ�� Ŀ���� �̵���Ų��.
	//-------------------------------------------------------------
	SetConsoleCursorPosition(hConsole, stCoord);
}


void cs_SetColor(CONSOLE_COLOR color)
{
//	SetConsoleTextAttribute(hConsole, static_cast<std::underlying_type<CONSOLE_COLOR>::type>(color));
	SetConsoleTextAttribute(hConsole, as_integer(color));
}