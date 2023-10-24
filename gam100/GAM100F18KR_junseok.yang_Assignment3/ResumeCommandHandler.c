/******************************************************************************
filename    ResumeCommandHandler.h
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines functions that handle the "resume" user command, which outputs
a list of the available verbs.

******************************************************************************/
#include "stdafx.h" /* UNREFERENCED_PARAMETER */
#include "ResumeCommandHandler.h" /* Function declarations */
#include "GameStateManager.h"
#include "GameState.h" /* GameState_EndGame */
#include "Utils.h"
#include "WorldData.h"


/* Handles the "resume" command, which outputs a list of available verbs */
void HandleResumeCommand(CommandData *command, GameState *gameState, WorldData *worldData)
{
	ClearScreen();

	PrintIndent(30, "\n");
	PrintCentered(2, "[ O P T I O N ]\n");
	PrintIndent(10, "\n");
	PrintCentered(2, "[R]esume\n");
	PrintCentered(2, "[C]redit\n");
	PrintCentered(2, "[Q]uit\n");
	PrintCentered(2, "R[S]tart\n");
	
	UNREFERENCED_PARAMETER(command);
	

	/* safety check on the parameters */
	if (gameState == NULL)
	{
		return; /* the parameters are invalid - take no action */
	}
	
	int option = getchar();

	if ((option == 'R') || (option == 'r'))
	{
		system("cls");
		WorldData_PrintIntroduction(worldData, gameState->currentRoomIndex);
		GameStateManagerSetNextState(GsTextAdventure);
		getchar();
	}

	else if ((option == 'q') || (option == 'Q'))
	{
		GameStateManagerSetNextState(GsQuit);
		getchar();
	}

	else if ((option == 'c') || (option == 'C'))
	{
		GameStateManagerSetNextState(GsCredits);
		getchar();
	}
	
	else if ((option == 's') || (option == 'S'))
	{
		GameStateManagerSetNextState(GsGameOver);
		ClearScreen();
	}
	
}