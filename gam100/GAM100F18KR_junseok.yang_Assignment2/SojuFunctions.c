/******************************************************************************
filename    SojuFunctions.c
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the functions to create a specific item, the "soju".

******************************************************************************/

#include "stdafx.h" /* UNREFERENCED_PARAMETER, NULL*/
#include "GameState.h" /* struct GameState, GameState_ChangeScore */
#include "GameFlags.h" /* GameFlags_IsInList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList, Room_SetDescription */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* Item_Create */
#include "WorldDataFactory.h"
#include "SojuFunctions.h" /* Function declarations */



typedef struct WorldData WorldData;


/* Helper: The action performed when the Soju is taken. */
void Soju_Take(CommandContext context, GameState* gameState, WorldData* worldData)
{

	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(worldData);

	/* safety check on the parameters */
	if (gameState == NULL)
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if the Soju has already been scored */
	if (!GameFlags_IsInList(gameState->gameFlags, "sojuScored"))
	{
		/* tell the user that something cool happens when they pick up the Soju */
		printf("picked up a soju with a lot of clean.\n");
		/* add to the user's score */
		GameState_ChangeScore(gameState, 144);
		/* the key has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "sojuScored");
	}
	
}

void Soju_Drink(CommandContext context, GameState* gameState, WorldData* worldData)
{
	Room* room; /* The current room */
	ItemList** roomItemsPtr; /* The list of items in the current room */
	Item* soju; /* The soju in the player's inventory */

	/* safety check on the parameters */
	if ((gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if the user is using the soju out of their inventory */
	if (context != CommandContext_Item_Inventory)
	{
		/* the user doesn't have the soju - inform the user of the problem and take no action */
		printf("You must have the soju before you can use it.\n");
		return;
	}


	/* check if the cage has already been broken and scored */
	if (GameFlags_IsInList(gameState->gameFlags, "Use or Drink sojuScored"))
	{
		/* the player already used the soju - inform the user of the problem and take no action */
		printf("You already used the soju here.\n");
		return;
	}
	else
	{
		/* get the current room */
		room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);

		/* get the list of items in the current room */
		roomItemsPtr = Room_GetItemList(room);
		if (roomItemsPtr == NULL)
		{
			return; /* take no action, as something is wrong - we should always have an item list */
		}

		/* Find the soju in the player's inventory - it should be there, since we are in the Inventory context */
		soju = ItemList_FindItem(gameState->inventory, "soju");

		/* Remove the soju from the user's inventory - they won't need it again */
		gameState->inventory = ItemList_Remove(gameState->inventory, soju);

		/* Tell the user what they did */
		printf("I drink soju with good taste. I found the end of another gameexit.\n");

		/* Add to the player's score */
		GameState_ChangeScore(gameState, 269);

		GameState_EndGame(gameState, "WOW!!!!   lucky guy!!!\n\nEnd the game in another way.\n\n");

		/* Update the room description to reflect the change in the room */
		Room_SetDescription(room, "This is room 6.  You are in a display room. There is no soju in room 6.\n");


		/* the soju has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "Use or Drink sojuScored");
	}
}
 


/* Build a "soju" object */
Item* Soju_Build()
{
	/* Create a "soju" item, using the functions defined in this file */
	return Item_Create("soju", "The clean soju break the little crack.\n", true, true, Soju_Drink, Soju_Take, NULL);
}