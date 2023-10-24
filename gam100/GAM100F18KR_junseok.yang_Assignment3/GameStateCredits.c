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



static const char * Ending[] =
{
	"___________           .___.__                 _________                    .___.__  __   ",
	"\\_   _____/ ____    __| _/|__| ____    ____   \\_   ___ \\_______   ____   __| _/|__|/  |_ ",
	" |    __)_ /    \\  / __ | |  |/    \\  / ___\\  /    \\  \\/\\_  __ \\_/ __ \\ / __ | |  \\   __\\",
	" |        \\   |  \\/ /_/ | |  |   |  \\/ /_/  > \\     \\____|  | \\/\\  ___// /_/ | |  ||  |  ",
	"/_______  /___|  /\\____ | |__|___|  /\\___  /   \\______  /|__|    \\___  >____ | |__||__|  ",
	"        \\/     \\/      \\/         \\//_____/           \\/             \\/     \\/           ",
	"",
	"",

};


void GameStateCreditsInit()
{
	int num = _countof(Ending);

	for (int i = 0; i < num; i++)
	{
		printf("%s ", Ending[i]);
		Wait(100);
		printf("\n");
	}


	printf("\n\n\n         [Ending Credit]\n\n");
	printf("             Game Producer JS// Game Engineer JS \n");
	Wait(1000);
	printf("             2018  (10/30~11/13)\n");
	Wait(1000);
	printf("             Thank you for playing!!\n");
	Wait(1000);
	printf("\n");

}
	void GameStateCreditsUpdate(){}
	void GameStateCreditsExit(){}


