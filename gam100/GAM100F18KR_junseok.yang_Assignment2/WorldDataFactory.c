/******************************************************************************
filename    WorldDataFactory.c
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the WorldData factory, which creates the WorldData objects used
in this game.

This could be used to create default states as well as loaded state.

******************************************************************************/
#include "WorldDataFactory.h" /* Function declarations */
#include "WorldData.h" /* WorldData_Create, WorldData_SetRoom */
#include "Room.h" /* Room_Create, Room_AddRoomExit, Room_GetItemList */
#include "ItemList.h" /* ItemList_Add */
#include "BrickFunctions.h" /* Brick_Build */
#include "GoldPieceFunctions.h" /* GoldPiece_Build */
#include "ExitDoorFunctions.h" /* ExitDoor_Build */
#include "FlowerFunctions.h" /* Flower_Build */
#include "PotionFunctions.h" /* Potion_Build */
#include "SojuFunctions.h" /* Soju_Build */
#include "StoneFunctions.h" /* Stone_Build */



/******************************************************************************
	Build room TEMPLATE
    Use this example function to build additional rooms
******************************************************************************/
Room* RoomN_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room;

	/* Create the room
	   include an initial room description */
	room = Room_Create("DEBUG: This is a template - Include a description for the room here\n");


	/* Exits
	   add one or more exits to allow navigation between rooms */
	Room_AddRoomExit(room, "north", 1);  /* 1 = the room index this exit connects to */

	/* Items
	   add items to the room */
	ItemList_AddItem(Room_GetItemList(room), ExitDoor_Build());

	/* Return the new room */
	return room;
}


/* TODO REQUIRED: Build room 0 */
Room* Room0_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room0;
	
	/* TODO REQUIRED: Call Room_Create with the Room 0 description:
	   "This is room 0. It is a display room with a cage in the middle. You can see a jeweled egg inside the cage.  There is a crack in the west wall, but you can't fit through it from this side.\n" */
	room0 = Room_Create("This is room 0. It is a display room with a cage in the middle. You can see a jeweled egg inside the cage.  There is a crack in the west wall, but you can't fit it from this side.\nThere is also a path leading East.\n");
	/* TODO REQUIRED: Add an Exit "north" to Room 1 */
	Room_AddRoomExit(room0, "north", 1);
	/* TODO BASIC: Add room exit shortcut for "n" */
	Room_AddRoomExitShortcut(room0, "n", 1);
	/* TODO REQUIRED: add an exit door to the list of items in the room, ExitDoor_Build() */
	ItemList_AddItem(Room_GetItemList(room0), ExitDoor_Build());
	/* TODO ADVANCED: (not required) update the description and add a room exit to the "east" */
	Room_SetDescription(room0, "This is room 0. It is a display room with a cage in the middle. You can see a jeweled egg inside the cage.  There is a crack in the west wall, but you can't fit it from this side.\nThere is also a path leading East.\n");
	
	Room_AddRoomExit(room0, "path", 3);

	Room_AddRoomExitShortcut(room0, "east", 3);
	Room_AddRoomExitShortcut(room0, "e", 3);
	
	/* TODO REQUIRED: DELETE this line when funciton is implemented, this avoids a warning, but will ruin your code */
	/*room = NULL;*/	

	/* return the new room */
	return room0;
}


/* TODO REQUIRED: Build room 1 */
Room* Room1_Build()
{
	/* TODO: Pre-declare a room pointer which we will use to build the new room */
	Room *room;
	/* TODO REQUIRED: Call Room_Create with the Room 1 description:
	   "This is room 1.  There is a large mirror here, and it shimmers as you approach.\n" */
	room = Room_Create("This is room 1.  There is a large mirror here, and it shimmers as you approach.\n");
	/* TODO REQUIRED: Add an Exit "through the mirror" to Room 2 */
	Room_AddRoomExit(room, "through the mirror", 2);
	/* TODO BASIC: Add exit shortcuts for "through mirror" and "mirror" */
	Room_AddRoomExitShortcut(room, "through mirror", 2);
	Room_AddRoomExitShortcut(room, "mirror", 2);
	/* TODO REQUIRED: Add an Exit "south" back to Room 0 */
	Room_AddRoomExit(room, "south", 0);
	/* TODO BASIC: Add room exit shortcut for "s" */
	Room_AddRoomExitShortcut(room, "s", 0);
	/* TODO REQUIRED: Add a brick to the list of items in the room */
	ItemList_AddItem(Room_GetItemList(room), Brick_Build());
	/* TODO: return the new room */
	return room;
}


/* TODO REQUIRED: Build room 2 */
Room* Room2_Build()
{
	/* TODO BASIC: Pre-declare a room pointer which we will use to build the new room */
	Room *room;
	/* TODO REQUIRED: Call Room_Create with the Room 2 description:
	   "This is room 2.  The room is isolated from the others, but you can see a crack in the east wall, just large enough to get through.\n" */
	room = Room_Create("This is room 2.  The room is isolated from the others, but you can see a crack in the east wall, just large enough to get through.\n");
	/* TODO REQUIRED: Add an Exit "east" to Room 0 */
	Room_AddRoomExit(room, "east", 0);
	/* TODO BASIC: Add exit shortcuts for "e" and "crack" */
	Room_AddRoomExitShortcut(room, "e", 0);
	Room_AddRoomExitShortcut(room, "crack", 0);
	/* TODO REQUIRED: Add a gold piece to the list of items in the room */
	ItemList_AddItem(Room_GetItemList(room), GoldPiece_Build());
	/* TODO BASIC: remove NULL and return the new room */
	return room;
}


/* TODO ADVANCED: Build room 3 */
Room* Room3_Build()
{
	Room *room;

	room = Room_Create("This is room 3. You find yourself deep in the forest. There are many wild flowers lining the path and you hear birds singing in the trees. The path extends to the West and you can see a clearing further East.\n");
	
	Room_AddRoomExit(room, "clearing", 4);

	Room_AddRoomExitShortcut(room, "e", 4);
	Room_AddRoomExitShortcut(room, "east", 4);
	
	Room_AddRoomExit(room, "path", 0);

	Room_AddRoomExitShortcut(room, "w", 0);
	Room_AddRoomExitShortcut(room, "west", 0);

	/*Flowers – this item can be added to your inventory*/
	ItemList_AddItem(Room_GetItemList(room), Flower_Build());

	return room;
}

/* TODO ADVANCED: Build room 4 */
Room* Room4_Build()
{
	Room *room;
	room = Room_Create("This is room 4. The forest clearing is quiet.A large stone covered in ancient writing sits in the middle of the clearing.There is a magical potion on top of the stone and it sparkles in the sunlight.The path is behind you to the West.\n");
	
	Room_AddRoomExit(room, "path", 3);

	Room_AddRoomExitShortcut(room, "w", 3);
	Room_AddRoomExitShortcut(room, "west", 3);

	Room_AddRoomExit(room, "past", 5);
	Room_AddRoomExitShortcut(room, "p", 5);

	/*Potion – this item can be added to your inventory*/
	ItemList_AddItem(Room_GetItemList(room), Potion_Build());

	return room;
}

Room* Room5_Build()
{
	Room *room;
	room = Room_Create("This is room 5. The dark and humid room has only hard stones, there is stone age of the past.There is a stone all around and a room next to it.\n");

	Room_AddRoomExit(room, "future", 4);
	Room_AddRoomExitShortcut(room, "f", 4);

	Room_AddRoomExit(room, "east", 6);
	Room_AddRoomExitShortcut(room, "e", 6);
	
	ItemList_AddItem(Room_GetItemList(room), Stone_Build());

	return room;
}

Room* Room6_Build()
{
	Room *room;
	room = Room_Create("This is room 6. It is a modern room that exists in the distant past. It is strange. Use the soju to leave the game.\n");

	Room_AddRoomExit(room, "west", 5);
	Room_AddRoomExitShortcut(room, "w", 5);

	return room;
}


/* ------------------------------------------------------- */
/* Create the world data for a new game */
/* ------------------------------------------------------- */
WorldData* CreateInitialWorldData()
{
	/* The new world data */
	WorldData* worldData;

	/* TODO REQUIRED: update room count to match the number of rooms you have created and added to the world
	   if this number doesn't match then your game will either crash or you will end up stuck in a broken room with no exits */
	int roomCount = 8;

	/* create the new WorldData object with 3 rooms */
	worldData = WorldData_Create("Welcome to my GAM100 Game!\n\n", roomCount);

	/* build each room and assign them to the world data */
	WorldData_SetRoom(worldData, 0, Room0_Build());
	/* TODO REQUIRED: add rooms 1 and 2 to the world data */
	WorldData_SetRoom(worldData, 1, Room1_Build());
	WorldData_SetRoom(worldData, 2, Room2_Build());
	/* TODO ADVANCED: add additional advanced rooms */
	WorldData_SetRoom(worldData, 3, Room3_Build());
	WorldData_SetRoom(worldData, 4, Room4_Build());

	WorldData_SetRoom(worldData, 5, Room5_Build());
	WorldData_SetRoom(worldData, 6, Room6_Build());
	 
	/* return the new object */
	return worldData;
}