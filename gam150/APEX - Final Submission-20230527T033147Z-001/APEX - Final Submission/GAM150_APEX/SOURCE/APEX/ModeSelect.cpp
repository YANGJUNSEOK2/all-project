/************************************************************************
*	File name : ModeSelect.cpp
*	Project name : APEX
*	Author	    Primary author : Haewon Shon
*			        Secondary author : Jookyung Lee
*			        Others : Junseok Yang, Wonju cho
*			        
*			        Functions for Mode Selection
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#include "ModeSelect.h"
#include "CommonLevel.h"
void ModeSelectLevel::Initialize()
{
    selection.SetName("selection");
    selection.sprite.LoadImage("texture/domination_2.png", m_renderer);
    selection.transform.SetScale(m_width, m_height);
    selection.transform.position.Set(0.f, 0.f, 0.f);
    AddObject(&selection);
    beep.SetName("beep");
    beep.sound.LoadSound("sound/menu_move.wav");
}

void ModeSelectLevel::Update(float dt)
{
    if(m_input->IsTriggered(SDL_SCANCODE_A) || m_input->IsTriggered(SDL_SCANCODE_LEFT)
        ||m_input->IsTriggered(SDL_SCANCODE_D) || m_input->IsTriggered(SDL_SCANCODE_RIGHT))
    {
        if(isDomination)
        {
            beep.sound.Play();
            isDomination = false;
            selection.sprite.Free();
            selection.sprite.LoadImage("texture/coin_2.png", m_renderer);
        }
        else
        {
            beep.sound.Play();
            isDomination = true;
            selection.sprite.Free();
            selection.sprite.LoadImage("texture/domination_2.png", m_renderer);
        }
    }

    if(m_input->IsTriggered(SDL_SCANCODE_SPACE))
    {
        beep.sound.Play();
        if(isDomination)
        {
            m_game->Change(LV_Domination);
        }
        else
        {
            m_game->Change(LV_CoinCollect);
        }
    }
    if (time > 0.5f)
    {
        if (isNormalScreen)
        {
            selection.sprite.Free();
            if(isDomination)
            {
                selection.sprite.LoadImage("texture/domination_2.png", m_renderer);
            }
            else
            {
                selection.sprite.LoadImage("texture/coin_2.png", m_renderer);
            }
        }
        else
        {
            selection.sprite.Free();
            if(isDomination)
            {
                selection.sprite.LoadImage("texture/domination_1.png", m_renderer);
            }
            else
            {
                selection.sprite.LoadImage("texture/coin_1.png", m_renderer);
            }
        }
        isNormalScreen = !isNormalScreen;
        time = 0.f;
    }


    time += dt;
    Render(dt);
}

void ModeSelectLevel::Close()
{
    ClearBaseState();

    beep.sound.Free();
    RemoveObject(&beep);
}