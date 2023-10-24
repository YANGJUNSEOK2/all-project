/************************************************************************
*	File name : KeyboardInput.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION
*************************************************************************/
#pragma once
#include  <unordered_map>

    class KeyboardInput
    {
    public:
        KeyboardInput() = default;
        ~KeyboardInput() = default;
        void Update();
        void pressKey(unsigned int keyID);
        void releaseKey(unsigned int keyID);
        bool isKeyDown(unsigned int keyID);
        bool isKeyPressed(unsigned int keyID);
    private:
        bool waskeydown(unsigned keyID);
        std::unordered_map<unsigned int, bool> m_KeyMap;
        std::unordered_map<unsigned int, bool> m_PreviousKeyMap;
    };
