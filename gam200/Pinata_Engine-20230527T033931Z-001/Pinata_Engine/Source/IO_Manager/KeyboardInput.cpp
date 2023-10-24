/************************************************************************
*	File name : KeyboardInput.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION
*************************************************************************/
#include "KeyboardInput.h"

    void KeyboardInput::Update()
    {
        for (auto& it : m_KeyMap) {
            m_PreviousKeyMap[it.first] = it.second;
        }
    }

    void KeyboardInput::pressKey(unsigned keyID)
    {
        m_KeyMap[keyID] = true;
    }

    void KeyboardInput::releaseKey(unsigned keyID)
    {
        m_KeyMap[keyID] = false;
    }

    bool KeyboardInput::isKeyDown(unsigned keyID)
    {
        auto it = m_KeyMap.find(keyID);
        if (it != m_KeyMap.end())
        {
            return it->second;
        }
        else
        {
            return false;
        }
    }

    bool KeyboardInput::isKeyPressed(unsigned keyID)
    {
        if (isKeyDown(keyID) == true && waskeydown(keyID) == false)
        {
            return true;
        }
        return false;
    }

    bool KeyboardInput::waskeydown(unsigned keyID)
    {
        auto it = m_PreviousKeyMap.find(keyID);
        if (it != m_PreviousKeyMap.end())
        {
            return it->second;
        }
        else
        {
            return false;
        }
    }



