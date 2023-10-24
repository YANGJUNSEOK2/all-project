/******************************************************************************
filename    FlowerFunctions.c
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the functions to create a specific item, the "flower".

******************************************************************************/

#include "stdafx.h" /* UNREFERENCED_PARAMETER, NULL*/
#include "FlowerFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_ChangeScore */
#include "GameFlags.h" /* GameFlags_IsInList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList, Room_SetDescription */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* Item_Create */
#include "TakeCommandHandler.h"

typedef struct WorldData WorldData;

/* Helper: The action performed when the Flower is taken. */
void Flower_Pick(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(worldData);


	/* safety check on the parameters */
	if (gameState == NULL)
	{
		return; /* take no action if the parameters are invalid */
	}


	
		/* tell the user that something cool happens when they pick up the flower*/
		printf("Pick up a pretty flower.\n");

		GameState_ChangeScore(gameState, 7);
		/* the flower has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "flowerScored");

		return;
	
}


	

/* Build a "flower" object */
Item* Flower_Build()
{	
	/* Create a "flower" item, using the functions defined in this file */
	return Item_Create("flower", "pretty flowers in an unknown place", true,false ,NULL, Flower_Pick, NULL);
}