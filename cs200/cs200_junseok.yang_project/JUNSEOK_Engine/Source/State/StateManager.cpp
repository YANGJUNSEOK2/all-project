/************************************************************************
*	File name : StateManager.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#include "StateManager.h"

void GameState::HandleEvents(Engine* game)
{
    game->getMouse().Mouse_Nothing();

    SDL_Event p_Event;
    while (SDL_PollEvent(&p_Event) != 0)
    {
        switch (p_Event.type)
        {
        case SDL_WINDOWEVENT:
            if (p_Event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                game->getWindow().ResizeWindow(p_Event.window.data1, p_Event.window.data2);
            }
            break;
        case SDL_QUIT:
            game->Quit();
            break;
        case SDL_MOUSEMOTION:
        {
            int x = static_cast<int>((p_Event.motion.x - game->getWindow().Get_Screen_Width() / 2) / game->getCamera().GetScale());
            int y = static_cast<int>((p_Event.motion.y - game->getWindow().Get_Screen_Height() / 2) / game->getCamera().GetScale());
            game->getMouse().SetMousePos(static_cast<float>(x), static_cast<float>(y));
        }
        break;
        case SDL_KEYDOWN:
            game->getInputs().SetKeyPressed(p_Event.key.keysym.scancode, SDL_KEYDOWN);

            break;
        case SDL_KEYUP:
            game->getInputs().SetKeyPressed(p_Event.key.keysym.scancode, SDL_KEYUP);
            if (p_Event.key.keysym.sym == SDLK_v)
            {
                game->getWindow().Set_Window_Vsync();
            }
            else if (p_Event.key.keysym.sym == SDLK_f)
            {
                game->getWindow().Change_Window_Type();
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            if (p_Event.button.button == SDL_BUTTON_LEFT)
            {
                game->getMouse().Mouse_Downed(MouseButton::Left);
            }
            else if (p_Event.button.button == SDL_BUTTON_RIGHT)
            {
                game->getMouse().Mouse_Downed(MouseButton::Right);
            }
            else if (p_Event.button.button == SDL_BUTTON_MIDDLE)
            {
                game->getMouse().Mouse_Downed(MouseButton::Wheel);
            }
        }
        break;
        case SDL_MOUSEBUTTONUP:
        {
            if (p_Event.button.button == SDL_BUTTON_LEFT)
            {
                game->getMouse().Mouse_Clicked(MouseButton::Left);
            }
            else if (p_Event.button.button == SDL_BUTTON_RIGHT)
            {
                game->getMouse().Mouse_Clicked(MouseButton::Right);
            }
            else if (p_Event.button.button == SDL_BUTTON_MIDDLE)
            {
                game->getMouse().Mouse_Clicked(MouseButton::Wheel);
            }
        }
        break;
        case SDL_MOUSEWHEEL:
        {
            const float SPEED_SCALE = 0.1f;

            if (p_Event.wheel.y > 0 && game->getCamera().GetScale() < 1)
            {
                game->getCamera().SetCameraZoom(SPEED_SCALE);
            }
            else if (p_Event.wheel.y < 0 && game->getCamera().GetScale() > 0.3)
            {
                game->getCamera().SetCameraZoom(-SPEED_SCALE);
            }
        }
        break;
        }
    }

    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        game->Quit();
    }
}

void GameState::FrameDelay(FPS* fpslimiter, float& m_fps)
{
    fpslimiter->Begin();
    m_fps = fpslimiter->End();
}
