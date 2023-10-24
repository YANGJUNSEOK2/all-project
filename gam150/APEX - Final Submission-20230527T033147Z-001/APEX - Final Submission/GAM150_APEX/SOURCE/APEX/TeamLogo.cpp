/************************************************************************
*	File name : TeamLogo.cpp
*	Project name : APEX
*	Author	    Primary author : Junseok Yang
*			        Secondary author : Wonju Cho
*			        
*			        Functions for Printing TeamLogo at the beginning
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#include "CommonLevel.h"
#include "TeamLogo.h"


void TeamLogo::Initialize()
{
    // digipenLogo
    teamLogo.SetName("teamLogo");
    teamLogo.transform.SetScale(State::m_width - 400, State::m_height-650 );
    teamLogo.sprite.LoadImage("texture/APEX_Logo.png", State::m_renderer);

    AddObject(&teamLogo);

    begin.SetName("begin");
    begin.sound.LoadSound("sound/begin.wav");

    begin.sound.Play();
}

void TeamLogo::Update(float dt)
{
    time += dt;
    if (time > 2)
        m_game->Change(LV_MainMenu);

    Render(dt);
}

void TeamLogo::Close()
{
    time = 0.f;
    ClearBaseState();

    begin.sound.Free();
    RemoveObject(&begin);
}


