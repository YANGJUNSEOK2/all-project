/************************************************************************
*	File name : MiathLibrary.h
*	Project name : apple
*   Author	    Primary author : Junseok Yang
*			    Secondary author : Seungguk Jang
*	File description : 
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

extern "C" MATHLIBRARY_API int GetRight(int x);

extern "C" MATHLIBRARY_API int GetLeft(int x);
