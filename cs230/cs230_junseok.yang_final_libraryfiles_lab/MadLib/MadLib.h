/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project:lab1
CourseNumber:cs230
Author:junseok.yang
Created:Spring 2019/3/22
------------------------------------------------------------------------*/

#pragma once


#ifdef MADLIB_EXPORTS
#define MADLIB_API __declspec(dllexport)
#else
#define MADLIB_API __declspec(dllimport)
#endif

extern "C" MADLIB_API const char * generate_madlib(
	const char * adjective,
	const char * verb,
	const char * noun
);
