/************************************************************************
*	File name : InputManager.cpp
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Control mouse and keyboard input
*	2021 summer Semester cs225 class project
*************************************************************************/
#include "InputManager.h"
#include <SFML/Window.hpp>
dyn_array InputManager::keyBoard{ static_cast<int>(InputManager::KeyboardMapping::COUNT) };

void InputManager::Init() noexcept
{
    int maxKeyMap = static_cast<int>(keyBoard.size());
    for (int i = 0; i < maxKeyMap; i++)
    {
        keyBoard[i] = false;
    }
}

void InputManager::SetKey(KeyboardMapping keyboard, bool isPress) noexcept
{
    keyBoard[static_cast<int>(keyboard)] = isPress;
}

bool InputManager::IsKeyDown(KeyboardMapping key) noexcept
{
    return keyBoard[static_cast<int>(key)];
}

bool InputManager::IsKeyReleased(KeyboardMapping key) noexcept
{
    return keyBoard[static_cast<int>(key)] == false && 
        waskeyBoard[static_cast<int>(key)] == true;
}

void InputManager::Update() noexcept
{
    int length = static_cast<int>(waskeyBoard.size());
    for (int i = 0; i < length; i++)
    {
        waskeyBoard[i] = keyBoard[i];
    }
}
