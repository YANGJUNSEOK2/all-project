/******************************************************************************/
/*!
	\file   Utils.c
	\author junseok.yang
	\par    Course: GAM100
	\par    Copyright ?2016 DigiPen (USA) Corporation.
	\brief
 */
/******************************************************************************/

#pragma warning(push)
#pragma warning(disable: 4001)
#include <time.h>
#pragma warning(pop)

#include "stdafx.h" /* NULL, malloc/free, printf, strcmp, */
#include "Utils.h"

/*------------------------------------------------------------------------------
// Private Consts:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Private Structures:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Private Variables:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Private Function Declarations:
//----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------*/

/* Perform a screen transition effect. */
void ScreenTransition()
{
	printf("\n\n\n");
	for (int i = 10; i < 50; ++i)
	{
		if (i % 2 == 0)
		{
			printf(" ¡ß");
			Wait(30);
		}
		else
		{
			printf(" ¡Þ");
			Wait(30);
		}
	}
}

void ScreenGameOver()
{
	for (int i = 0; i < 1; i++)
	{
		printf("\n\n\n\n                                   [");
		Wait(150);
		printf(" G");
		Wait(150);
		printf(" A");
		Wait(150);
		printf(" M");
		Wait(150);
		printf(" E");
		Wait(150);
		printf("  ");
		Wait(150);
		printf(" O");
		Wait(150);
		printf(" V");
		Wait(150);
		printf(" E");
		Wait(150);
		printf(" R");
		Wait(150);
		printf("  ");
		Wait(150);
		printf(" R");
		Wait(150);
		printf(" E");
		Wait(150);
		printf(" S");
		Wait(150);
		printf(" T");
		Wait(150);
		printf(" A");
		Wait(150);
		printf(" R");
		Wait(150);
		printf(" T");
		Wait(150);
		printf(" !");
		Wait(150);
		printf(" ]");
		Wait(500);
	}
}

void ScreenLoading()
{
		printf("\n\n[==================                         Loading Wait                           ==================]\n ");
	
	for (int x = 0; x < 100; x++)
	{
		printf("=");
		Wait(30);
	}
	printf("\n");
}

void ScreenChange()
{
	for (int i = 0; i < 1; i++)
	{
		printf("\n\n\n\n                                   [");
		Wait(150);
		printf(" T");
		Wait(150);
		printf(" E");
		Wait(150);
		printf(" X");
		Wait(150);
		printf(" T");
		Wait(150);
		printf("  ");
		Wait(150);
		printf(" A");
		Wait(150);
		printf(" D");
		Wait(150);
		printf(" V");
		Wait(150);
		printf(" E");
		Wait(150);
		printf(" N");
		Wait(150);
		printf(" T");
		Wait(150);
		printf(" U");
		Wait(150);
		printf(" R");
		Wait(150);
		printf(" E");
		Wait(150);
		printf(" ]");
		Wait(150);
	}
}

/* Clear the screen. */
void ClearScreen()
{
	/* This calls the system command, "cls", which clears the screen. */
	system("cls");
}

/* Wait for a specified number of milliseconds. */
void Wait(long waitTime)
{
	clock_t	wakeTime;
	wakeTime = waitTime + clock();
	while (wakeTime > clock())
	{
		/* Do nothing while waiting. */
	}
}

/*------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------*/

