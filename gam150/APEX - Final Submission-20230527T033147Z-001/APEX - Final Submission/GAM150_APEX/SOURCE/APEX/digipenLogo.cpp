/************************************************************************
*	File name : digipenLogo.cpp
*	Project name : APEX
*	Author	    Primary author : Junseok Yang
*			        Secondary author : Wonju Cho
*			        
*			        Functions for DigiPen Logo at the beginning of the game.
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#include "CommonLevel.h"
#include "digipenLogo.h"

void DigipenLogo::Initialize()
{
    // digipenLogo
    digipenLogo.SetName("DigiPen");
    digipenLogo.transform.SetScale(State::m_width-500, State::m_height-500);
    digipenLogo.sprite.LoadImage("texture/DigiPen_BLACK.png", State::m_renderer);

    AddObject(&digipenLogo);

    begin.SetName("begin");
    begin.sound.LoadSound("sound/game_begin.wav");

    begin.sound.Play();
}

void DigipenLogo::Update(float dt)
{
    time += dt;
    if (time > 2)
        m_game->Change(LV_TeamLogo);

    Render(dt);
}

void DigipenLogo::Close()
{
    time = 0.f;
    ClearBaseState();

    begin.sound.Free();
    RemoveObject(&begin);
}
