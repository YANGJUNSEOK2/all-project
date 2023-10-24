/******************************************************************************
filename    CommandHandler.h
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file declares the command handler, which parses commands and executing functions.

******************************************************************************/
#pragma once

typedef struct CommandData CommandData;
typedef struct GameState GameState;
typedef struct WorldData WorldData;

/* Handles the command data and executes it against the game and world state */
void HandleCommand(CommandData* command, GameState *gameState, WorldData* worldData);