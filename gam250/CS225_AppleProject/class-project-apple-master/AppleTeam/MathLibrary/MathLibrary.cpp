/************************************************************************
*	File name : MathLibrary.cpp
*	Project name : apple
*   Author	    Primary author : Junseok Yang
*			   econdary author : Seungguk Jang
*	File description : Locate sfml window using gameboard Index
*	2021 summer Semester cs225 class project
*************************************************************************/
#include "pch.h" 
#include <utility>
#include <limits.h>
#include "MathLibrary.h"

int GetRight(int x)
{
    return x - 1;
}

int GetLeft(int x)
{
    return x + 1;
}