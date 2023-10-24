/******************************************************************************
filename    ResumeCommandHandler.h
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file declares functions that handle the "resume" user command, which outputs
a list of the available verbs.

******************************************************************************/
#pragma once

typedef struct CommandData CommandData;
typedef struct GameState GameState;
typedef struct WorldData WorldData;


/* Handles the "resume" command, whic outputs a list of available verbs */
void HandleResumeCommand(CommandData* command, GameState *gameState, WorldData *worldData);

void PrintIndent(int num, char*discrip);
void PrintCentered(int num, char*discrip);
