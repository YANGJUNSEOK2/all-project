/************************************************************************
*	File name : Level2.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#include "Level2.h"
#include "Level1.h"
#include "Level3.h"
#include "../Shader/glCheck/glCheck.hpp"

Level2 Level2::m_Level2;

void Level2::Init(Engine* game)
{
    game->getCamera().InitCamera(game->getWindow().Get_Screen_Width(), game->getWindow().Get_Screen_Height());
    std::cout << "Level2 Init" << std::endl;
    game->getWindow().Change_Window_Color({ 50,80,10,255 });

    game->InitShader();

    black.Init(-200.f, -400.f, 100.f, 100.f, 0.f,{ 255, 255, 255, 255 }, "Texture/rectangle.png");

    AniFace.Init(-200.f, 400.f, 50.f, 50.f, 0.f, { 255,255,255,255 }, "Texture/icon.png");

    T.Init(0.f, 0.f, 90.f, 100.f, 4.3f,7.2f, { 255,255,255,255 }, "assets/malgungothic_2.png");

    m_sprite.Init();
    m_Font.init("Fonts/sunsin.ttf", 64);

    image = Image(game->getWindow().Get_Screen_Width(), game->getWindow().Get_Screen_Height(), Color{ 255,255,255,225 });

    AniFace.Init(-650, -200, 200, 300, 6, { 255,255,255,255 }, "Texture/face.png");
    AniDora.Init(-400, -200, 200, 300, 4, { 255,255,255,255 }, "Texture/dora.png");

    glCheck(glLineWidth(3.0f));// GL::set_line_width

    m_MaxFPS = 60.f;
    m_fpslimiter.Init(m_MaxFPS);

    std::cout
        << "===========LEVEL2 ===============================\n"
        << "===========SCREEN SHOT -> SPACE BAR==============\n"
        << "===========CAMERA ===============================\n"
        << "===========CAMERA TRANSLATION W A S D============\n"
        << "===========CAMERA  ZOOM MOUSE WHEEL==============\n"
        << "===========LEVEL1 -> MOUSE LEFT==================\n"
        << "===========LEVEL3 -> MOUSE RIGHT=================\n";
}

void Level2::Close(Engine* game)
{
    std::cout << "Level2 Close" << std::endl;
}

void Level2::Pause()
{
    std::cout << "Level2 Paused" << std::endl;
}

void Level2::Resume()
{
    std::cout << "Level2 Resumed" << std::endl;
}

void Level2::Update(Engine* game)
{
    game->getCamera().UpdateCamera();
    FrameDelay(&m_fpslimiter, m_FPS);
    game->getWindow().Show_FPS_Inwindow(m_FPS);


    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_W))
    {
        game->getCamera().CameraTranslation(0, 5);
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_S))
    {
        game->getCamera().CameraTranslation(0, -5);
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_A))
    {
        game->getCamera().CameraTranslation(-5, 0);
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_D))
    {
        game->getCamera().CameraTranslation(5, 0);
    }

    if (game->getMouse().Is_Mouse_Clicked(MouseButton::Left))
    {
        game->ChangeState(Level1::Instance(), game);
    }
    if (game->getMouse().Is_Mouse_Clicked(MouseButton::Right))
    {
        game->ChangeState(Level3::Instance(), game);
    }

    game->getWindow().Swapbufferwindow();
}


void Level2::Draw(Engine* game)
{
    game->Update_Shaders();
    game->getShader().UseEnable();

    T.Adding_Screen(game, true);
    black.Adding_Screen(game);
    AniFace.Adding_Screen(game);

    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_SPACE))
    {
        auto screenshot_image = screenShot.capture_screenshot_of_back_buffer_to_image(game->getWindow().Get_Screen_Width(), game->getWindow().Get_Screen_Height());
        screenshot_image.SaveToPNG("Screenshot_Full.png");
    }

    m_sprite.Begin();
    m_Font.Draw(m_sprite, "Level 2!!!!!", Vector2<float>{-300.0f, 300.0f}, Vector2<float>{1.0f, 1.0f}, -1.0f, { 255, 0, 0, 255 });
    m_Font.Draw(m_sprite, "SHOW THE ANIMATION AND SPRITE(TEXTURE)!!!", Vector2<float>{-300.0f, 250.0f}, Vector2<float>{1.0f, 1.0f}, -1.0f, { 255, 255, 0, 255 });
    m_Font.Draw(m_sprite, "SCREEN SHOT -> SPACE BAR", Vector2<float>{-300.0f, 200.0f}, Vector2<float>{1.0f, 1.0f}, -1.0f, { 0, 255, 0, 255 });
    m_Font.Draw(m_sprite, "USING SUNSIN FONT!!", Vector2<float>{-300.0f, 150.0f}, Vector2<float>{1.0f, 1.0f}, -1.0f, { 255, 0, 255, 255 });
    m_sprite.End();
    m_sprite.SpriteRenderBatch();

    AniDora.Adding_Screen(game, true, 10);
    AniFace.Adding_Screen(game, true, 30);

    game->getShader().UnUseDisable();
}