/******************************************************************************
filename    StoneFunctions.c
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the functions to create a specific item, the "stone".

******************************************************************************/

#include "stdafx.h" /* UNREFERENCED_PARAMETER, NULL*/
#include "StoneFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_ChangeScore */
#include "GameFlags.h" /* GameFlags_IsInList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList, Room_SetDescription */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* Item_Create */
#include "SojuFunctions.h" /* Key_Build */


/* Helper: The action performed when the Stone is taken. */
void Stone_Take(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);

	/* Give the user a hint about how the stone might be used, whenever it is picked up. */
	printf("The stone feels too heavy in your hand.\n");
}


/* Helper: The action performed when the Stone is used. */
void Stone_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	Room* room; /* The current room */
	ItemList** roomItemsPtr; /* The list of items in the current room */
	Item* stone; /* The Stone in the player's inventory */

	/* safety check on the parameters */
	if ((gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if the user is using the stone out of their inventory */
	if (context != CommandContext_Item_Inventory)
	{
		/* the user doesn't have the Stone - inform the user of the problem and take no action */
		printf("You must have the stone before you can use it.\n");
		return;
	}

	/* check if the cage has already been broken and scored */
	if (GameFlags_IsInList(gameState->gameFlags, "findsojuScored"))
	{
		/* the player already used the stone - inform the user of the problem and take no action */
		printf("You already used the stone here.\n");
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

		/* Find the Stone in the player's inventory - it should be there, since we are in the Inventory context */
		stone = ItemList_FindItem(gameState->inventory, "stone");

		/* Remove the Stone from the user's inventory - they won't need it again */
		gameState->inventory = ItemList_Remove(gameState->inventory, stone);

		/* Tell the user what they did */
		printf("You smash the open room with the stone, and the stone crumbles.  You can now reach the clean soju inside.\n");

		/* Add to the player's score */
		GameState_ChangeScore(gameState, 89);

		/* Update the room description to reflect the change in the room */
		Room_SetDescription(room, "This is room 5.  You are in a display room. \n");

		/* Add an stone to the current room, since the cage has been bashed open */
		*roomItemsPtr = ItemList_Add(*roomItemsPtr, Soju_Build());

		/* the stone has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "findsojuScored");
	}


}


/* Build a "stone" object */
Item* Stone_Build()
{
	/* Create a "stone" item, using the functions defined in this file */
	return Item_Create("stone", "A hard stone of indeterminate origin", true, false, Stone_Use, Stone_Take, NULL);
}