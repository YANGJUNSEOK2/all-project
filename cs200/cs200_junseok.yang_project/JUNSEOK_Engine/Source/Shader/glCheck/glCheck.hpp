/************************************************************************
*	File name : glCheck.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once

void glCheckError(const char* file, unsigned int line, const char* expression);
void glClearErrors();


// Note that this macro calls glClearErrors, does expression, semicolon, and then calls glCheckError,
// so you shouldn't use this macro under an if statement without { } and
// you shouldn't use it in a return statement.
#ifdef _DEBUG
#define glCheck(expr)                                                                                                  \
    glClearErrors();                                                                                                   \
    (expr);                                                                                                            \
    glCheckError(__FILE__, __LINE__, #expr)
#else
#define glCheck(expr) (expr)
#endif