/******************************************************************************
filename    PickCommandHandler.h
author      junseok.yang
DP email    wnstjryang@gamil.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file declares functions that handle the "pick" user command, which calls
an item-specific function on a given item

******************************************************************************/

#pragma once

typedef struct CommandData CommandData;
typedef struct GameState GameState;
typedef struct WorldData WorldData;


/* Handles the "pick" command, which removes an item from the current room and adds it to the user's inventory */
void HandlePickCommand(CommandData* command, GameState *gameState, WorldData *worldData);