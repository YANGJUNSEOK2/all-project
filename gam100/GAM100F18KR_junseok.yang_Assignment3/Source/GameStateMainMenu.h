/******************************************************************************/
/*!
	\file   GameStateMainMenu.h
	\author      junseok.yang
	\par    Course: GAM100
	\par    Copyright ?2016 DigiPen (USA) Corporation.
	\brief
 */
/******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
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

	void PrintIndent(int num, char*discrip);
	void PrintCentered(int num, char*discrip);
	

/*!
 \brief
 */
extern void GameStateMainMenuInit();

/*!
 \param	dt Change in time (in seconds) since last game loop.
 */
extern void GameStateMainMenuUpdate(float dt);

/*!
 \brief
 */
extern void GameStateMainMenuExit();

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

