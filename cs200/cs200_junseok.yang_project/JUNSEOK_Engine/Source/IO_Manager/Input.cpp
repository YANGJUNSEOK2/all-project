/************************************************************************
*	File name : Input.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#include "Input.hpp"

//Key Memory
std::bitset<MaxKeyboard> m_KeyPressed;
std::bitset<MaxKeyboard> m_Keytriggered;
std::bitset<MaxKeyboard> m_KeyReleased;

void Inputs::Reset()
{
    m_KeyReleased.reset();
    m_Keytriggered.reset();
}

void Inputs::SetKeyPressed(SDL_Scancode key, SDL_EventType eType)
{
    if (eType == SDL_KEYDOWN)
    {
        m_KeyPressed.set(key);
        m_Keytriggered.set(key);
    }
    else if (eType == SDL_KEYUP)
    {
        m_KeyReleased.set(key);
        m_KeyPressed.reset(key);
    }
}

bool Inputs::IsKeyPressed(SDL_Scancode key)
{
    if (key >= MaxKeyboard) {
        return false;
    }
    return m_KeyPressed[key];
}

bool Inputs::IsKeytriggered(SDL_Scancode key)
{
    if (key >= MaxKeyboard) {
        return false;
    }
    return m_Keytriggered[key];
}

bool Inputs::IsKeyReleased(SDL_Scancode key)
{
    if (key >= MaxKeyboard) {
        return false;
    }
    return m_KeyReleased[key];
}

bool Inputs::IsAnyKeyPressed()
{
    return m_KeyPressed.any();
}

bool Inputs::IsAnyKeytriggered()
{
    return m_Keytriggered.any();
}

bool Inputs::IsAnyKeyReleased()
{
    return m_KeyReleased.any();
}
