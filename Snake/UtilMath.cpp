﻿#include "SnakePCH.h"

int UtilMath::GetRand(int range, int operand)
{
	srand(GetTickCount()*(operand + 10));
	return rand() % range;
}

float UtilMath::GetRandFloat()
{
	srand(GetTickCount()*(10));
	return rand();
}

