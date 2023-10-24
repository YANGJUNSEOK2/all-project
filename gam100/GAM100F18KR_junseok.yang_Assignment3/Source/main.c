/******************************************************************************
filename    main.c
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file implements the main function and game loop.

******************************************************************************/
#include "stdafx.h" /* NULL, bool */
#include "GameStateManager.h"

/* The main program loop */
int main()
{
	/* ------------------------------------------------------------------------ */
	/* Initilization and Setup */
	/* ------------------------------------------------------------------------ */

	/* Initialize the game state manager. */
	GameStateManagerInit();

	/* ------------------------------------------------------------------------ */
	/* GAME LOOP */
	/* ------------------------------------------------------------------------ */

	/* Loop until the game is no longer running. */
	while (GameStateManagerIsRunning())
	{
		/* Update the game state manager. */
		GameStateManagerUpdate(0.0f);
	}

	/* ------------------------------------------------------------------------ */
	/* Cleanup and Exit */
	/* ------------------------------------------------------------------------ */

	/* Exit the game state manager. */
	GameStateManagerExit();



	/* TODO REQUIRED: Move the following variables to GameStateTextAdventure. */
#if 0
	/* ------------------------------------------------------------------------ */
	/* Initilization and Setup */
	/* ------------------------------------------------------------------------ */
	//GameState* gameState; /* The game state, reflecting the user's progress */
	//WorldData* worldData; /* The world data */
	//CommandList* commandList; /* The set of supported commands */
	//CommandData command; /* The command entered by the user */
#endif

	/* TODO REQUIRED: Move the following function calls to GameStateTextAdventureInit(). */
#if 0
	/* create the initial game objects */
	//gameState = CreateInitialGameState();
	//worldData = CreateInitialWorldData();
	//commandList = CreateCommandList();

	///* initialize the command CommandData values */
	//command.commandList = commandList;
	//command.context = CommandContext_User;

	///* print the world introduction*/
	//WorldData_PrintIntroduction(worldData, gameState->currentRoomIndex);
#endif

	/* TODO REQUIRED: Move the code _inside_ the while-loop to GameStateTextAdventureUpdate().
		 The while-loop itself is no longer needed! */
#if 0
	/* ------------------------------------------------------------------------ */
	/* GAME LOOP */
	/* ------------------------------------------------------------------------ */
	/* while the game is running, accept input and handle commands */
	while (gameState->isRunning)
	{
		/* print command prompt */
		printf("\nWhat is your command?\n>> ");

		/* accept user input */
		ParseCommand(GetDefaultInputFunc(), &command);

		/* include an empty line before printing the result of a command */
		printf("\n");

		/* handle the command */
		HandleCommand(&command, gameState, worldData);
	}
#endif

	/* TODO REQUIRED: Move the clean up and exit code to GameStateTextAdventureExit(). */
#if 0
	/* ------------------------------------------------------------------------ */
	/* Cleanup and Exit */
	/* ------------------------------------------------------------------------ */
	WorldData_Free(&worldData);
	GameState_Free(&gameState);
	CommandList_Free(&commandList);

	/* wait for input before closing the command window */
	getchar();
#endif

	/* cleanly exit */
	return 0;
}