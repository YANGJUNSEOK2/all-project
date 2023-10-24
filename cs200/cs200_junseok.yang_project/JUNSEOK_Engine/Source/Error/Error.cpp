/************************************************************************
*	File name : Error.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/
#include"Error.h"
#include <cstdlib>
#include <iostream>
#include <SDL.h>
  void FindError(std::string p_errorString)
    {
        std::cout << p_errorString << std::endl;
        std::cout << "Enter any KEY to quit... ";
        int temp;
        std::cin >> temp;
        SDL_Quit();
        exit(69);
    }
