/******************************************************************************
filename    PickCommandHandler.c
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines functions that handle the "pick" user command, which calls
an item-specific function on a given item

******************************************************************************/

#include "stdafx.h" /* NULL, printf */
#include "PickCommandHandler.h" /* Function declarations */
#include "CommandData.h" /* struct CommandData */
#include "GameState.h" /* struct GameState */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Add, ItemList_Remove */
#include "Item.h" /* Item_IsCarryable, ItemFunc, Item_GetTakeFunc */

/* Handles the "pick" command, which removes an item from the current room and adds it to the user's inventory */
void HandlePickCommand(CommandData *command, GameState* gameState, WorldData* worldData)
{
	Item* pickItem; /* the item removed from the room and added to the user's inventory */
	Room* room; /* the current room */
	ItemList** roomItemPtr; /* the list of items in the current room */
	ItemFunc pickFunc; /* The function to be called for the given item when it is pick */
	

	/* safety check on the parameters */
	if ((command == NULL) || (command->noun == NULL) || (gameState == NULL) || (worldData == NULL))
	{
		return; /* pick no action if the parameters are invalid */
	}

	

	/* retrieve the current room */
	room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);
	
	/* get the current room's item list */
	roomItemPtr = Room_GetItemList(room);
	if (roomItemPtr == NULL)
	{
		return; /* there was no room or item list pointer - something is wrong.  take no action */
	}

	if (gameState->currentRoomIndex != 3)
	{
		printf("You cannot pick %s\n", command->noun);
		return;
	}

	/* find the item in the current room's item list, using the command noun */
	pickItem = ItemList_FindItem(*roomItemPtr, command->noun);
	if (pickItem == NULL)
	{
		/* the item is not carry- inform the user of the problem and pick no action */
		printf("You cannot pick the %s.\n", command->noun);
		return;
	}

	/* check if the item is carryable */
	if (Item_IsCarryable(pickItem) == false)
	{
		/* the item was not found - inform the user of the problem and pick no action */
		printf("You do not see a %s here.\n", command->noun);
		return;
	}

	/* remove the item from the room */
	*roomItemPtr = ItemList_Remove(*roomItemPtr, pickItem);

	/* add the item to the user's inventory */
	gameState->inventory = ItemList_Add(gameState->inventory, pickItem);

	/* inform the user of the successful action */
	printf("You have picked up the %s.\n", command->noun);

	/* get the "pick" function for this item, if any (it is optional) */
	pickFunc = Item_GetTakeFunc(pickItem);
	if (pickFunc != NULL)
	{
		/* call the pick function with the Room context, since that's where the item was */
		pickFunc(CommandContext_Item_Room, gameState, worldData);
	}
}