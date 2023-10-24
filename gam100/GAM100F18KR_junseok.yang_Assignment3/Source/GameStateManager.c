/******************************************************************************/
/*!
	\file   GameStateManager.c
	\author      junseok.yang
	\par    Course: GAM100
	\par    Copyright ?2016 DigiPen (USA) Corporation.
	\brief
 */
/******************************************************************************/

#include "stdafx.h"
#include "GameStateManager.h"
#include "GameStateTable.h"

/*------------------------------------------------------------------------------
// Private Consts:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Private Structures:
//----------------------------------------------------------------------------*/

typedef struct
{
	GAMESTATE	current;	/* Index of the current game state. */
	GAMESTATE	previous;	/* Index of the previous game state. */
	GAMESTATE	next;		/* Index of the next game state. */

} GameState;

/*------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Private Variables:
//----------------------------------------------------------------------------*/

static GameState gameState;

/*------------------------------------------------------------------------------
// Private Function Declarations:
//----------------------------------------------------------------------------*/

static bool	GameStateIsChanging();

/*------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Initialize the game state manager. */
void GameStateManagerInit()
{
	/* Set the current game state to invalid. */
	gameState.current = GsInvalid;

	/* Set the initial game state to launch the game. */
	gameState.next = GsInitial;
}

/*----------------------------------------------------------------------------*/
/* Update the game state manager. */
void GameStateManagerUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	if (GameStateIsChanging())
	{
		/* Exit the current game state. */
		GameStateExecuteExit(gameState.current);

		/* Load the new menu state. */
		gameState.current = gameState.next;

		/* Initialize the new game state. */
		GameStateExecuteInit(gameState.current);
	}

	/* Update the current game state. */
	GameStateExecuteUpdate(gameState.current, dt);

}

/*----------------------------------------------------------------------------*/
/* Shutdown the game state manager. */
void GameStateManagerExit()
{
}

/*----------------------------------------------------------------------------*/
/* Determine if the game is still running. */
bool GameStateManagerIsRunning()
{
	return gameState.next != GsQuit;
}

/*----------------------------------------------------------------------------*/
/* Set the next game state to run. */
void GameStateManagerSetNextState(GAMESTATE nextState)
{
	if (GameStateIsValid(nextState) || GameStateIsSpecial(nextState))
	{
		gameState.next = nextState;
	}
	else
	{
#ifdef _DEBUG
		/* In debug mode, print a message that an error has occurred. */
		printf("\nERROR: Invalid game state: %d\n", nextState);
#endif
	}
}

/*------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Determine if a game state change has been requested. */
static bool	GameStateIsChanging()
{
	return (gameState.current != gameState.next);
}
