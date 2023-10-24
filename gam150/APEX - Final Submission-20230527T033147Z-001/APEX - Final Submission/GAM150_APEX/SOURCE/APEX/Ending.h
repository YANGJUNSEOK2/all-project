/************************************************************************
*	File name : Ending.h
*	Project name : APEX
*	Author	    Primary author : Haewon Shon
*	        			Secondary author : Wonju Cho
*	        			Others : Junseok Yang, Jookyung Lee
*
*	        			header for Ending.cpp
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#pragma once
#include "engine\State.h"

class Ending : public State
{
    friend class Game;
protected:
    Ending() : State() {}
    ~Ending() override {}

    // Derived initialize function
    void Initialize() override;
    // Derived Update function-
    void Update(float dt) override;
    // Derived Close function
    void Close() override;

private:
    Object winCharacterImage, backGround, winnerText,end_sound;
};