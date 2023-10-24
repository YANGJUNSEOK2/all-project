/************************************************************************
*	File name : Input.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include <glew.h>
#include <SDL.h>
#include <bitset>
#include "../MathLibrary/MathLibrary.hpp"

#define MaxKeyboard 1024

class Inputs
{
public:
    //use Inputs functions
    static Inputs& getInstance()
    {
        static Inputs input;
        return input;
    }
    //Key & Mouse Reset
    void Reset();
    //Key set
    void SetKeyPressed(SDL_Scancode key, SDL_EventType eType);
    //Key Pressed
    static bool IsKeyPressed(SDL_Scancode key);
    //Key triggered
    static bool IsKeytriggered(SDL_Scancode key);
    //Key Released
    static bool IsKeyReleased(SDL_Scancode key);
    //Any Key Pressed
    static bool IsAnyKeyPressed();
    //Any Key triggered
    static bool IsAnyKeytriggered();
    //Any Key Released
    static bool IsAnyKeyReleased();
private:
};
