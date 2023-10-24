/************************************************************************
*	File name : Credit.h
*	Project name : APEX
*	Author	    Primary author : Junseok Yang
*			        Secondary author : Wonju Cho
*			        Others : Haewon Shon, Jookyung Lee
*
*			        header for Credit.cpp
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"

class Credit : public State
{
    friend class Game;
    enum Page{page1, page2, page3};
protected:
    Credit() : State() {}
    ~Credit() override {}

    void Initialize() override;
    void Update(float dt) override;
    void Close() override;

private:
    void ChangeNextPage();
    Object creditImage, creditSound;
    float cameraHeight;
    Page page;
};
