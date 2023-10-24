/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project:lab1
CourseNumber:cs230
Author:junseok.yang
Created:Spring 2019/3/22
------------------------------------------------------------------------*/

// MadLib.cpp : Defines the exported functions for the DLL application.
//

#include "MadLib.h"
#include <string>

namespace 
{
	std::string Output;
}

extern "C" MADLIB_API const char * generate_madlib(
	const char * adjective,
	const char * verb,
	const char * noun
)
{
	Output = "There once was a ";
	Output += adjective;
	Output += " programmer who wanted to use C++ to ";
	Output += verb;
	Output += " the ";
	Output += noun;
	Output += ".";
	return Output.c_str();
}

