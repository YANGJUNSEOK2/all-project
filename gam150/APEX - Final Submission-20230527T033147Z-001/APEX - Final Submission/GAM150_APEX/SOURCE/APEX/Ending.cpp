/************************************************************************
*	File name : Ending.cpp
*	Project name : APEX
*	Author	    Primary author : Haewon Shon
*	        			Secondary author : Wonju Cho
*	        			Others : Junseok Yang, Jookyung Lee
*	        			
*	        			Functions for Ending Scene
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#include "CommonLevel.h"

void Ending::Initialize()
{
    end_sound.SetName("end_sound");
    end_sound.sound.LoadSound("sound/final_win.wav");
    end_sound.sound.Play();

    camera.position.Set(0, 0, 0);
    
    backGround.SetName("background");
    backGround.sprite.LoadImage("texture/UI/win.png", m_renderer);
    backGround.transform.SetScale(m_width/3.f, m_height);
    backGround.transform.position.Set(0.f, 0.f, 0.f);
    backGround.sprite.color = SDL_Color{ 255, 255, 255, 255 };
    backGround.sprite.activeAnimation = true;
    backGround.sprite.SetFrame(3);
    backGround.sprite.SetSpeed(3.f);
    AddObject(&backGround);

    mainFont = TTF_OpenFont("font/JaykopDot.ttf", 64);

    const char* imageName = nullptr;
    int winner = 0;
    if(m_game->p1WinCount == 2)
    {
        winner = m_game->p1Character;
        winnerText.text.SetText("P1 WIN!", mainFont);
        AddObject(&winnerText);
    }
    if(m_game->p2WinCount == 2)
    {
        winner = m_game->p2Character;
        winnerText.text.SetText("P2 WIN!", mainFont);
        AddObject(&winnerText);
    }
    switch(winner)
    {
    case 1:
        imageName = "texture/character/win/junseok_win.png";
        break;
    case 2:
        imageName = "texture/character/win/jookyung_win.png";
        break;
    case 3:
        imageName = "texture/character/win/wonju_win.png";
        break;
    case 4:
        imageName = "texture/character/win/haewon_win.png";
        break;
    }
    winCharacterImage.SetName("winCharacterImage");
    winCharacterImage.sprite.LoadImage(imageName, m_renderer);
    winCharacterImage.transform.position.Set(0.f, 20.f, 0.f);
    winCharacterImage.transform.SetScale(m_height/4.f, m_height/2.f);
    winCharacterImage.sprite.color = SDL_Color{ 255, 255, 255, 255 };
    winCharacterImage.sprite.rewindAnimation = true;
    winCharacterImage.sprite.activeAnimation = true;
    winCharacterImage.sprite.SetFrame(3);
    if(winner == 4)
    {
        winCharacterImage.sprite.SetFrame(2);
    }
    winCharacterImage.sprite.SetSpeed(2.f);
    AddObject(&winCharacterImage);

    winnerText.SetName("winnerText");
    winnerText.transform.SetScale(m_height / 4.f, m_height / 8.f);
    winnerText.transform.position.Set(0.f, 0.f, 0.f);
    winnerText.text.color = SDL_Color{ 0,0,0,255 };
    winnerText.text.isHud = true;
    AddObject(&winnerText);
}

void Ending::Update(float dt)
{
    if(m_input->IsTriggered(SDL_SCANCODE_SPACE))
    {
        m_game->Change(LV_MainMenu);
    }
    // Must be one of the last functions called at the end of State Update
    Render(dt);
}

void Ending::Close()
{
    m_game->p1WinCount = 0;
    m_game->p2WinCount = 0;
    // Wrap up state
    ClearBaseState();

    end_sound.sound.Free();
    RemoveObject(&end_sound);
}