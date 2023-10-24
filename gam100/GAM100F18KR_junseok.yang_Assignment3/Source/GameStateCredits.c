/******************************************************************************/
/*!
\file   GameStateCredits.c
\author junseok.yang
\par    Course: GAM100
\par    Copyright ?2016 DigiPen (USA) Corporation.
\brief
*/
/******************************************************************************/

#include "stdafx.h"
#include "GameStateCredits.h"
#include "GameStateManager.h"
#include "Utils.h"



static const char * Credit[] =
{
	"  ________                        _________                    .___.__  __  ._.",
	" /  _____/_____    _____   ____   \\_   ___ \\_______   ____   __| _/|__|/  |_| |",
	"/   \\  ___\\__  \\  /     \\_/ __ \\  /    \\  \\/\\_  __ \\_/ __ \\ / __ | |  \\   __\\ |",
	"\\    \\_\\  \\/ __ \\|  Y Y  \\  ___/  \\     \\____|  | \\/\\  ___// /_/ | |  ||  |  \\|",
	" \\______  (____  /__|_|  /\\___  >  \\______  /|__|    \\___  >____ | |__||__|  __",
	"        \\/     \\/      \\/     \\/          \\/             \\/     \\/           \\/",
	"",
	"",

};


void GameStateCreditsInit()
{
	int num = _countof(Credit);

	for (int i = 0; i < num; i++)
	{
		printf("%s ", Credit[i]);
		Wait(100);
		printf("\n");
	}


	printf("\n\n\n         [Game Credit]\n\n");
	printf("             Game Producer JS// Game Engineer JS \n");
	Wait(1000);
	printf("             2018  (10/30~11/13)\n");
	Wait(1000);
	printf("             Thank you for playing!!\n");
	Wait(1000);
	printf("\n");

}
	void GameStateCreditsUpdate(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		printf("Press Enter!!");

		getchar();

		GameStateManagerSetNextState(GsMainMenu);
	}

	void GameStateCreditsExit()
	{
		ScreenTransition();

		ClearScreen();
	}


