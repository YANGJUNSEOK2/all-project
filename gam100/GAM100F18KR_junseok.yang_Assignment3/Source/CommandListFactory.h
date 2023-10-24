/******************************************************************************
filename    CommandFactory.h
author      junseok.yang
DP email    wnstjryang@gmail.com
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file declares the CommandList factory, which creates the commands used
in this game.

******************************************************************************/
#pragma once

typedef struct CommandList CommandList;

/* Create the command list with all commands used in this game.*/
CommandList* CreateCommandList();