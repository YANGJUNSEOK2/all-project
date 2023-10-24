/************************************************************************
*	File name : ModeSelect.h
*	Project name : APEX
*	Author	    Primary author : Haewon Shon
*			        Secondary author : Jookyung Lee
*			        Others : Junseok Yang, Wonju cho
*
*			        header for ModeSelect.cpp
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#pragma once
#include "engine\State.h"
#include "CustomBaseObject.h"

class ModeSelectLevel : public State
{
    friend class Game;
protected:
    ModeSelectLevel() : State() {};
    ~ModeSelectLevel() override {};

    void Initialize() override;
    void Update(float dt) override;
    void Close() override;

private:
    Object selection,beep;
    bool isDomination = true, isNormalScreen = true;
    float time = 0.f;
};