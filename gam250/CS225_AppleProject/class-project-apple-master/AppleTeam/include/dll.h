#pragma once
/************************************************************************
*	File name : dll.h
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Load dll using loadlibrary. if load fail, LogError occur.
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include <Windows.h>
#include <string>

typedef int(*FNPTR)(int);

HINSTANCE hModule = LoadLibrary(L"C:/class-project-apple/AppleTeam/AppleLibrary/WindowPos.dll");

FNPTR fn = (FNPTR)GetProcAddress(hModule, "GetUp");