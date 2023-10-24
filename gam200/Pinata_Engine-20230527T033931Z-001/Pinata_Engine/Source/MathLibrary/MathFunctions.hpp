/************************************************************************
*	File name : MathFunctions.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester
*************************************************************************/
#pragma once
//#define _USE_MATH_DEFINES
#include <SDL.h>



constexpr float PI = 3.1415926535897932384626433832795f;

//Convert Degree to Radian
inline float DegreeToRadian(float p_Degree) {
	return static_cast<float>(p_Degree * (M_PI / 180.0f));
}
