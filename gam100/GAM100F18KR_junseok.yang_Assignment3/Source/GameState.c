/******************************************************************************
filename    GameState.c
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file implements the GameState interface, which is used to reflect the user state
in the game.

******************************************************************************/
/* from GameState.h: stdafx.h, used here for NULL, malloc/free, printf */
#include "stdafx.h"
#include "GameState.h" /* Function declarations */
#include "GameStateManager.h"
#include "ItemList.h" /* ItemList_Free */
#include "GameFlags.h" /* GameFlags_Free */
#include "Utils.h"	/* ClearScreen */
#include "GameStateMainMenu.h"
#include "GameStateCredits.h"


static const char * GoodBye[] =
{
"     ________                  ._____________             ._.",
"    /  _____/  ____   ____   __| _/\\______   \\___.__. ____| |",
"   /   \\  ___ /  _ \\ /  _ \\ / __ |  |    |  _<   |  |/ __ \\ |",
"   \\    \\_\\  (  <_> |  <_> ) /_/ |  |    |   \\___  \\  ___/\\|",
"    \\______  /\\____/ \\____/\\____ |  |______  // ____|\\___  >_",
"          \\/                   \\/         \\/ \\/         \\/\\/",

};


/* Create an empty game state object */
GameState* GameState_Create()
{
	GameState* gameState; /* the new object we will return */

	/* allocate memory for the new object */
	gameState = (GameState*)malloc(sizeof(GameState));
	if (gameState == NULL)
	{
		return NULL; /* malloc can fail! */
	}

	/* assign empty values to all members */
	gameState->score = 0;
	gameState->currentRoomIndex = 0;
	gameState->inventory = NULL;
	gameState->gameFlags = NULL;

	/* TODO BASIC: Delete the isRunning variable. */
	/*gameState->isRunning = true;*/

	/* return the new object */
	return gameState;
}


/* Free the memory associated with a game-state object */
void GameState_Free(GameState** gameStatePtr)
{
	/* safety check on the parameters */
	if ((gameStatePtr == NULL) || (*gameStatePtr == NULL))
	{
		return; /* take no action if no valid object was provided */
	}

	/* free the inventory */
	ItemList_Free(&(*gameStatePtr)->inventory);

	/* free the game flags */
	GameFlags_Free(&(*gameStatePtr)->gameFlags);

	/* free the object */
	free(*gameStatePtr);

	/* set the incoming pointer to NULL*/
	*gameStatePtr = NULL;
}


/* Modify the score, with appropriate user information */
void GameState_ChangeScore(GameState* gameState, int modifier)
{
	/* safety check on the parameters */
	if (gameState == NULL)
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if any action is needed*/
	if (modifier == 0)
	{
		return; /* no action needed */
	}

	/* modify the score */
	gameState->score += modifier;

	/* check if the modifier is positive or negative */
	if (modifier > 0)
	{
		/* the modifier was positive, so output a positive message */
		printf("You have gained %d points.  ", modifier);
	}
	else
	{
		/* the modifier was negative, so output a negative message */
		printf("You have lost %d points.  ", modifier);
	}

	/* output the new score total */
	printf("Your new score is %d.\n", gameState->score);
}


/* End the game, with appropriate user information */
void GameState_EndGame(GameState* gameState, const char* message)
{
	/* safety check on the parameters */
	if (gameState == NULL)
	{
		return; /* take no action if the parameters are invalid */
	}

	/* TODO BASIC: Clear the screen before displaying the results text. */
	ClearScreen();
	/* if a message was provided, output it now */
	if (message != NULL)
	{
		printf(message);
	}

	PrintCentered(2, "You have quit the game.\n");

	/* output the final score */
	PrintCentered(2,"Your final score is ");
	printf("%d\n\n", gameState->score);
	/* output a clean goodbye message, so the user knows the game is exiting intentionally */
	PrintCentered(2,"\n\n");
	int num = _countof(GoodBye);
	/* second, print each line in the digipenlogo[] array. */
	for (int i = 0; i < num; i++)
	{
		printf("%s ", GoodBye[i]);
		printf("\n");
	}
	/* third, print a couple extra blank lines. */
	printf("\n\n");

	GameStateCreditsInit();

	/* TODO REQUIRED: Tell the game state manager to switch to the GsGameOver state. */
	GameStateManagerSetNextState(GsGameOver);
//#if 0
	/* set the isRunning state so the game quits on the next loop */
	/*gameState->isRunning = false;*/
//#endif
}