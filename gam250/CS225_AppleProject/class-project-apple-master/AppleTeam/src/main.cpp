/************************************************************************
*	File name : main.cpp
*	Project name : apple
*	Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : main.cpp file initiate all, update and shutdown.
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include "Engine.h"
#include "Splash.h"
#include "Level1.h"
#include <iostream>
#include "dll.h"

int main()
{
	auto& en = Engine::EngineIns();

	if (!hModule)
	{
		Engine::LoggerIns().LogError("Cannot get dll");
		Engine::LoggerIns().LogError("Don't you git clone at c drive??");
	}
	if (!fn)
	{
		Engine::LoggerIns().LogError("Not GetProcAddress");
	}
	else
	{
		int i = 0;
		Engine::LoggerIns().LogDebug(fn(i));
		Engine::LoggerIns().LogDebug("Successful load dll. The value have to 1");
	}
	en.SceneManagerIns().EmplaceScene<Splash>();
	en.SceneManagerIns().EmplaceScene<Level1>();
	try
	{
		if (en.Init() == true)
		{
			while (!en.IsGameEnd())
			{
				en.Update();
			}
		}
		en.ShutDown();
	}
	catch (const std::exception& e)
	{
		en.LoggerIns().LogError(e.what());
		return -1;
	}
	if (hModule)
	{
		FreeLibrary(hModule);
	}
}