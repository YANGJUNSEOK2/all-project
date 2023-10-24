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
	
	for (int i = 0; i < 10; i++)
	{
		printf("If you want to How to Play\n");
		Wait(50);
		printf("Press HELF(H) key in game\n");
		Wait(50);
		printf("Press LOOK(L) key in game\n");
		Wait(50);
		printf("\n");
	}

}

void GameStateHowtoPlayUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);


	/*printf("Enter command: ");

	int option = getchar();


	if ((option == 'p') || (option == 'P'))
	{
		int num = _countof(Play);

		for (int i = 0; i < num; i++)
		{
			printf("%s ", Play[i]);

			printf("\n");
		}
		
		GameStateManagerSetNextState(GsMainMenu);
	}



	else if ((option == 'q') || (option == 'Q'))
	{

		GameStateManagerSetNextState(GsQuit);
	}

	else
	{

		GameStateManagerSetNextState(GsInvalid);
	}
	while ((option = getchar()) != '\n' && option != EOF);*/
}

void GameStateHowtoPlayExit()
{

	ScreenChange();

	ClearScreen();
}