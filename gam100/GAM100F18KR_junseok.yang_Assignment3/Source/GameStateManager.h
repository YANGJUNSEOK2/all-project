/******************************************************************************/
/*!
	\file   GameStateManager.h
	\author      junseok.yang
	\par    Course: GAM100
	\par    Copyright ?2016 DigiPen (USA) Corporation.
	\brief
 */
/******************************************************************************/

#pragma once

#include "GameStateTable.h"

#ifdef __cplusplus
extern "C" {	/* Assume C declarations for C++ */
#endif

/*------------------------------------------------------------------------------
// Public Consts:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Structures:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------*/

/* Initialize the game state manager. */
extern void GameStateManagerInit();

/* Update the game state manager. */
extern void GameStateManagerUpdate(float dt);

/* Shutdown the game state manager. */
extern void GameStateManagerExit();

/* Determine if the game is still running. */
extern bool GameStateManagerIsRunning();

/* Set the next game state to run. */
extern void GameStateManagerSetNextState(GAMESTATE nextState);

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

