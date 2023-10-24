/******************************************************************************
filename    DrinkCommandHandler.c
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines functions that handle the "drink" user command, which calls
an item-specific function on a given item

******************************************************************************/

#include "stdafx.h" /* NULL, printf */
#include "DrinkCommandHandler.h" /* Function declarations */
#include "CommandData.h" /* struct CommandData, CommandContext */
#include "GameState.h" /* struct GameState */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList */
#include "ItemList.h" /* ItemList_FindItem */
#include "Item.h" /* ItemFunc, Item_GetUseFunc */


/* Handles the "drink" command, which calls an item-specific function on a given item */
void HandleDrinkCommand(CommandData* command, GameState* gameState, WorldData* worldData)
{
	Item* drinkItem; /* the item to be drinked */
	Room* room; /* the current room */
	ItemList** roomItemsPtr; /* the list of items in the current room */
	ItemFunc drinkFunc; /* The function to be called for the given item when it is drinked */
	CommandContext drinkContext = CommandContext_User; /* the context used for the "drink" function*/
	

	/* safety check on the parameters */
	if ((command == NULL) || (command->noun == NULL) || (gameState == NULL) || (worldData == NULL))
	{
		return;  /* take no action if the parameters are invalid */
	}
	 
	/*gameState->inventory*/
		/* search for the item in the user's inventory, which takes precedence over the current room */
		drinkItem = ItemList_FindItem(gameState->inventory, command->noun);


		if (drinkItem != NULL)
		{
			/* the item was found in the user's inventory, so we're going to use the Inventory context*/
			drinkContext = CommandContext_Item_Inventory;
		}
		else
		{
			/* retrieve the current room */
			room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);


			/* retrieve the set of items in the current room */
			roomItemsPtr = Room_GetItemList(room);
			/* retrieve the item from the list of items in teh current room */
			if (roomItemsPtr != NULL)
			{
				drinkItem = ItemList_FindItem(*roomItemsPtr, command->noun);
			}
			if (drinkItem != NULL)
			{
				/* the item was found in the room, so we're going to use the Room context */
				drinkContext = CommandContext_Item_Room;
			}
		}
	
		if (gameState->currentRoomIndex != 4&& gameState->currentRoomIndex != 6)
		{
			printf("You cannot drink %s\n", command->noun);
			return;
		}

		if (Item_IsDrinkable(drinkItem) == false)
		{
			/* the item is not carryable - inform the user of the problem and take no action */
			printf("You cannot drink the %s.\n", command->noun);
			return;
		}
		

	/* check if the item has been found anywhere */
	if (drinkItem == NULL)
	{
		/* no "drink" function was defined, so the item cannot be used - inform the user of the problem and take no action*/
		printf("You cannot use a %s here.\n", command->noun);
		return;
	}

	/* get the "drink" function for this item, if any */
	drinkFunc = Item_GetUseFunc(drinkItem);
	if (drinkFunc == NULL)
	{
		/* the item was not found - inform the user of the problem and take no action */
		printf("You do not see a %s here.\n", command->noun);
		return;
	}

	/* call the "drink" function with the appropriate context */
	drinkFunc(drinkContext, gameState, worldData);
}