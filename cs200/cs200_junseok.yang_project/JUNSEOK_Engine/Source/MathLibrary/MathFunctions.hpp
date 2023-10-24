/************************************************************************
*	File name : MathFunctions.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
//#define _USE_MATH_DEFINES



constexpr float PI = 3.1415926535897932384626433832795f;
constexpr float TWO_PI = 3.1415926535897932384626433832795f * 2.0f;

//Convert Degree to Radian
inline float DegreeToRadian(float p_Degree) {
	return static_cast<float>(p_Degree * (PI / 180.0f));
}
