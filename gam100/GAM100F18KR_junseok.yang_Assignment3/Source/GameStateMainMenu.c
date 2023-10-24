/******************************************************************************/
/*!
	\file   GameStateMainMenu.c
	\author Doug Schilling
	\par    Course: GAM100
	\par    Copyright ?2016 DigiPen (USA) Corporation.
	\brief
 */
/******************************************************************************/

#include "stdafx.h"
#include "GameStateMainMenu.h"
#include "GameStateManager.h"
#include "GameStateGameOver.h"
#include "Utils.h"

/*------------------------------------------------------------------------------
// Private Consts:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Private Structures:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Private Variables:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Private Function Declarations:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------*/

void PrintIndent(int num,char*discrip)
{
	for (int x = 0; x < num; x++)
	{
		printf("	");
	}
	printf("%s", discrip);
}

void PrintCentered(int num, char*discrip)
{
	for (int x = 0; x < num; x++)
	{
		PrintIndent(1,"	 ");
	}
	printf("%s", discrip);
}

void GameStateMainMenuInit()
{
	
	/* TODO BASIC: Display the name of your text adventure as simple text or ASCII graphics. */
	static const char* ZzanAdventure[] =
	{
	"																	",
	"																	",
	"   #########     #########         ##          ###        ##       ",
	"          #             #         ####         ## #       ##       ",
	"         #             #         #    #        ##  #      ##       ",
	"        #             #         #      #       ##   #     ##       ",
	"       #             #         ##########      ##    #    ##       ",
	"      #             #         ############     ##     #   ##       ",
	"     #             #         #            #    ##      #  ##       ",
	"    #             #         #              #   ##       # ##       ",
	"   #########     ######### #                #  ##        ###       ",
	};
	int num = _countof(ZzanAdventure);

	for (int i = 0; i < num; i++)
	{
		printf("%s ", ZzanAdventure[i]);

		printf("\n");
	}
	/* TODO REQUIRED: Display the following main menu options: */
	PrintIndent(30, "\n");
	PrintCentered(2,"Select an option:\n");
	PrintCentered(2," (P)lay\n");
	PrintCentered(2," (Q)uit\n");
	PrintCentered(2, " (H)ow to Play\n");
	PrintCentered(2," (C)redit\n\n");

	/* TODO ADVANCED: Implement one or more functions, such as PrintIndent() or PrintCentered(),
		 that procedurally determine where to display strings of text on the screen.
		 For example: PrintIndent(20, "(P)lay"); will display "(P)lay" starting at the 20th column.
		 Use these functions to display the menu text in a nicely presented fashion. */
}

void GameStateMainMenuUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	/* TODO BASIC: Print the message "Enter command: " to the screen. */
	printf("Enter command: ");

	/* TODO: Read the user input. */
	int option = getchar();
	
	/* TODO REQUIRED: Check for 'p' or 'P' to be entered. */
		if ((option=='p')||(option=='P'))
		{
			/* TODO REQUIRED: Tell the game state manager to switch to the GsTextAdventure state. */
			GameStateManagerSetNextState(GsTextAdventure);
		}

	/* TODO REQUIRED: Check for 'q' or 'Q' to be entered. */
	
		else if ((option == 'q') || (option == 'Q'))
		{
	/* TODO REQUIRED: Tell the game state manager to quit the game (GsQuit). */
			GameStateManagerSetNextState(GsQuit);
		}

		else if ((option == 'H') || (option == 'h'))
		{
			GameStateManagerSetNextState(GsHowtoPlay);
		}

		else if ((option == 'c') || (option == 'C'))
		{
			GameStateManagerSetNextState(GsCredits);
		}
		
		else
		{
		/* TODO ADVANCED: Display an error message if an invalid command is entered. */
			printf("Invalid command.  Press 'P' or 'Q'\n");
			GameStateManagerSetNextState(GsInvalid);
		}
			
	
		while ((option = getchar()) != '\n' && option != EOF);
}

void GameStateMainMenuExit()
{
	/* TODO ADVANCED: Implement an interesting screen transition effect. See function definition in Utils.c. */
	ScreenChange();
	/* TODO BASIC: Call the utility function to clear the screen (See Utils.h). */
	ClearScreen();
}

/*------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------*/

