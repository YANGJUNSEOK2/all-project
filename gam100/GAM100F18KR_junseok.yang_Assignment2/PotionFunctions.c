/******************************************************************************
filename    PotionFunctions.c
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the functions to create a specific item, the "potion".

******************************************************************************/

#include "stdafx.h" /* UNREFERENCED_PARAMETER, NULL*/
#include "PotionFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_ChangeScore */
#include "GameFlags.h" /* GameFlags_IsInList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList, Room_SetDescription */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "Item.h" /* Item_Create */



/* Helper: The action performed when the Potion is Pick. */
void Potion_Pick(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(gameState);
	UNREFERENCED_PARAMETER(worldData);
	
	/* Give the user a hint about how the Potion might be used, whenever it is picked up. */
	printf("Picked up some red liquid.\n");
}


/* Helper: The action performed when the Potion is used. */
void Potion_Drink(CommandContext context, GameState* gameState, WorldData* worldData)
{
	Room* room; /* The current room */
	ItemList** roomItemsPtr; /* The list of items in the current room */
	Item* potion; /* The potion in the player's inventory */

	/* safety check on the parameters */
	if ((gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if the user is using the Potion out of their inventory */
	if (context != CommandContext_Item_Inventory)
	{
		/* the user doesn't have the Potion - inform the user of the problem and take no action */
		printf("You must have the potion before you can use it.\n");
		return;
	}


	/* check if the cage has already been broken and scored */
	if (GameFlags_IsInList(gameState->gameFlags, "Use or Drink PotionScored"))
	{
		/* the player already used the potion - inform the user of the problem and take no action */
		printf("You already used the potion here.\n");
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

		/* Find the Potion in the player's inventory - it should be there, since we are in the Inventory context */
		potion = ItemList_FindItem(gameState->inventory, "potion");

		/* Remove the potion from the user's inventory - they won't need it again */
		gameState->inventory = ItemList_Remove(gameState->inventory, potion);

		/* Tell the user what they did */
		printf("You feel stronger, healthier.  The liquid must have come from the fountain of youth.\n");

		/* Add to the player's score */
		GameState_ChangeScore(gameState, 100);

		/* Update the room description to reflect the change in the room */
		Room_SetDescription(room, "This is room 4.  You are in a display room. There is no potion in room 4.\n");


		/* the potion has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "Use or Drink PotionScored");
	}
}


/* Build a "potion" object */
Item* Potion_Build()
{
	/* Create a "potion" item, using the functions defined in this file */
	return Item_Create("potion", "A small red potion of indeterminate origin", true, true ,Potion_Drink, Potion_Pick, NULL);
}