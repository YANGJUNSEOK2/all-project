/************************************************************************
*	File name : PauseState.cpp
*	Project name : APEX
*	Author	Primary author : Wonju Cho
*			Secondary author : Junseok Yang
*			
*			Functions for Pause
*	All content © 2019 DigiPen (USA) Corporation, all rights reserved.
*************************************************************************/
#include "CommonLevel.h"

void PauseState::Initialize()
{
	m_backgroundColor = {255, 255, 255, 255};

	// Set Camera
	// You don't need to do this anymore
	//camera.Initialize(int(State::m_width), int(State::m_height));
	// Set position of the camera
	camera.position.Set(0, 0, 0);

	// Set main font
	// Load the font file to use as a main font
	// and set the default size of it
	mainFont = TTF_OpenFont("font/Default.ttf", 48);

    pauseImage.sprite.LoadImage("texture/pause_back_to_the_game.png", m_renderer);
    pauseImage.transform.SetScale(m_width/2.f, m_height/2.f);

    pauseImage.transform.position.Set(0.f, 0.f, 0.f);
    AddObject(&pauseImage);

    pauseImageStatus = PauseImage::BACK_TO_THE_GAME;

    beep.SetName("beep");
    beep.sound.LoadSound("sound/menu_move.wav");
}

void PauseState::Update(float dt)
{
	/******************* State ******************/
    if (m_input->IsTriggered(SDL_SCANCODE_RETURN) || m_input->IsTriggered(SDL_SCANCODE_SPACE))
    {
        beep.sound.Play();
        switch (pauseImageStatus)
        {
        case PauseImage::BACK_TO_THE_GAME:
            m_game->Resume();
            break;
        case PauseImage::EXIT:
            m_game->Quit();
            break;
        default:
            break;
        }
    }
    PauseSelect();
	// Must be one of the last functions called at the end of State Update
	Render(dt);
}

void PauseState::Close()
{
	// Wrap up state
	ClearBaseState();

    beep.sound.Free();
    RemoveObject(&beep);
}

void PauseState::PauseSelect()
{
    if (m_input->IsTriggered(SDL_SCANCODE_UP))
    {
        switch (pauseImageStatus)
        {
        case PauseImage::BACK_TO_THE_GAME:
            pauseImageStatus = PauseImage::EXIT;
            break;
        case PauseImage::TOGGLE_FULLSCREEN:
            pauseImageStatus = PauseImage::BACK_TO_THE_GAME;
            break;
        case PauseImage::EXIT:
            pauseImageStatus = PauseImage::TOGGLE_FULLSCREEN;
            break;
        }
        PauseImageChange();
    }
    if (m_input->IsTriggered(SDL_SCANCODE_DOWN))
    {
        switch (pauseImageStatus)
        {
        case PauseImage::BACK_TO_THE_GAME:
            pauseImageStatus = PauseImage::TOGGLE_FULLSCREEN;
            break;
        case PauseImage::TOGGLE_FULLSCREEN:
            pauseImageStatus = PauseImage::EXIT;
            break;
        case PauseImage::EXIT:
            pauseImageStatus = PauseImage::BACK_TO_THE_GAME;
            break;
        }
        PauseImageChange();
    }
}

void PauseState::PauseImageChange()
{
    pauseImage.sprite.Free();
    switch (pauseImageStatus)
    {
    case PauseImage::BACK_TO_THE_GAME:
        pauseImage.sprite.LoadImage("texture/pause_back_to_the_game.png", m_renderer);
        break;
    case PauseImage::TOGGLE_FULLSCREEN:
        pauseImage.sprite.LoadImage("texture/pause_toggle_fullscreen.png", m_renderer);
        break;
    case PauseImage::EXIT:
        pauseImage.sprite.LoadImage("texture/pause_exit.png", m_renderer);
        break;
    }
}