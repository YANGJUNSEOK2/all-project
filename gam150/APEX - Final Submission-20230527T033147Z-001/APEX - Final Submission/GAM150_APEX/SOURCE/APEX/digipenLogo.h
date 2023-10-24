/************************************************************************
*	File name : digipenLogo.h
*	Project name : APEX
*	Author	    Primary author : Junseok Yang
*			        Secondary author : Wonju Cho
*
*			        header for digipenLogo.cpp
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#pragma once
#include "engine\State.h"
#include "CustomBaseObject.h"
#include "Player.h"

class DigipenLogo : public State
{
    friend class Game;
protected:

    DigipenLogo() : State() {};
    ~DigipenLogo() override {};

    // Derived initialize function
    void Initialize() override;
    // Derived Update function-
    void Update(float dt) override;
    // Derived Close function
    void Close() override;

private:
    Object digipenLogo,begin;
    float time = 0.f;
};