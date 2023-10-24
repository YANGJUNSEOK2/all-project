/******************************************************************************
filename    TalkCommandHandler.c
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines functions that handle the "talk" user command, which calls
an item-specific function on a given item

******************************************************************************/

#include "stdafx.h" /* NULL, printf */
#include "TalkCommandHandler.h" /* Function declarations */
#include "CommandData.h" /* struct CommandData */
#include "GameState.h" /* struct GameState */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetNextRoomIndex, Room_Print, INVALID_DIRECTION_ID */

/* Handles the "talk" command, which outputs a description of an item or the current room */
void HandleTalkCommand(CommandData *command, GameState *gameState, WorldData *worldData)
{
	Room* currentTalk = 0; /* the room we are currently in */

	/* safety check on the parameters */
	if ((command == NULL) || (command->noun == NULL) || (gameState == NULL) || (worldData == NULL))
	{
		return; /* talk no action if the parameters are invalid */
	}
	currentTalk = WorldData_GetRoom(worldData, gameState->currentRoomIndex);

	if (gameState->currentRoomIndex == 4)
	{
		printf("You open your mouth in an attempt to read the ancient characters on the rock. \nYour effort is cut short as the sun fades and a hushed whisper comes on the wind.\nAll you are able to make out is ¡°Only drink the potion if¡¦¡± and then the wind dies down and the clearing is calm again.¡±\n");
	}
	else if (gameState->currentRoomIndex == 5)
		printf("Hear the cries of animals I have not seen.\n");
	else if (gameState->currentRoomIndex == 6)
	{
		printf("In a modern room, a creepy voice loudly.........."); printf("would you want drink? \n");
	}
	else
		printf("You mumble something under your breath as you begin to go mad.\n");
}