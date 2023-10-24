/******************************************************************************/
/*!
\file   GameStateHowtoPlay.c
\author junseok.yang
\par    Course: GAM100
\par    Copyright ?2016 DigiPen (USA) Corporation.
\brief
*/
/******************************************************************************/

#include "stdafx.h"
#include "GameStateHowtoPlay.h"
#include "GameStateManager.h"
#include "Utils.h"



static const char * Play[] =
{
	"            ",
	"            ",
	"  __________.__                ",
	"  \\______   \\  | _____  ___.__.",
	"   |     ___/  | \\__  \\<   |  |",
	"   |    |   |  |__/ __ \\\\___  |",
	"   |____|   |____(____  / ____|",
	"                      \\/\\/     ",

};


void GameStateHowtoPlayInit()
{
	
	printf("\n\n\n         [How to Play]\n\n");
	printf("             If you want to How to Play\n");
		Wait(1000);
	printf("             Press HELP(H) key in game\n");
		Wait(1000);
	printf("             Press LOOK(L) key in game\n");
		Wait(1000);
	printf("\n");
	

	int num = _countof(Play);
	
	for (int i = 0; i < num; i++)
	{
		printf("%s ", Play[i]);
		Wait(100);
		printf("\n");
	}

}

void GameStateHowtoPlayUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	printf("Press Enter!!");

	getchar();

	GameStateManagerSetNextState(GsMainMenu);
}

void GameStateHowtoPlayExit()
{
	ScreenTransition();

	ClearScreen();
}


