/************************************************************************
*	File name : Utils.cpp
*	Project name : APEX
*	Author	Primary author : Haewon Shon
*			Secondary author : Junseok Yang
*			
*			Random Function for Utility
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#include "Utils.h"

void RandomInit()
{
    srand(static_cast<unsigned int>(time(NULL)));
}

int GetRandomNumber(int min, int max)
{
    int randomNum = rand() % (max - min + 1) + min;

    return randomNum;
}