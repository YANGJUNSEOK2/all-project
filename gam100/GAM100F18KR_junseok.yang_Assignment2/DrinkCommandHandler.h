/******************************************************************************
filename    DrinkCommandHandler.h
author      junseok.yang
DP email    wnstjryang@gamil.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file declares functions that handle the "drink" user command, which calls
an item-specific function on a given item

******************************************************************************/

#pragma once

typedef struct CommandData CommandData;
typedef struct GameState GameState;
typedef struct WorldData WorldData;


/* Handles the "drink" command, which calls an item-specific function on a given item */
void HandleDrinkCommand(CommandData* command, GameState *gameState, WorldData *worldData);