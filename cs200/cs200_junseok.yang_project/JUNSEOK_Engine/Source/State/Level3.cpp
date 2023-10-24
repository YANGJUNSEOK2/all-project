/************************************************************************
*	File name : Level3.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#include "Level3.h"
#include "Level2.h"
#include "Level1.h"
#include <random>


Level3 Level3::m_Level3;

void Level3::Init(Engine* game)
{
    std::cout << "Level3 Init" << std::endl;
    game->getWindow().Change_Window_Color({ 0,0,0,255 });
    A.Initial();

    m_ParticleBatch = new SpriteParticle;

    // Initialize the particle batch and use a lambda function to define the update
    m_ParticleBatch->init(1000, 500.f, Texture::GetTexture("Texture/particle.png"),
        [](Particle& particle, float deltaTime) 
    {
        particle.position += particle.velocity / deltaTime;
        particle.color.a = (GLubyte)(particle.life * 255.0f);
    });

    m_particleEngine.addParticleBatch(m_ParticleBatch);

    Text.Init(0, 0, 500, 500, NULL, { 200,100,50,255 }, "Texture/earth.png");
    Ani.Init(-400, 200, 200, 300, 4, { 255,255,255,255 }, "Texture/animation.png");

    m_MaxFPS = 60.f;
    m_fpslimiter.Init(m_MaxFPS);
    game->getCamera().InitCamera(game->getWindow().Get_Screen_Width(), game->getWindow().Get_Screen_Height());
    std::cout 
        << "============ Level3 =====================================\n"
        << "=============particle ===================================\n"
        << "=============particle =====GENERATE======================\n"
        << "=============PRESS -> G =================================\n"
        << "=============animation ==================================\n"
        << "=============animation =====MOVE=========================\n"
        << "=============UP   DOWN   LEFT   RIGHT====================\n"
        << "=============texture ====================================\n"
        << "=============test test test test test test ==============\n"
        << "=============LEVEL2 -> MOUSE LEFT========================\n"
        << "=============LEVEL1 -> MOUSE RIGHT=======================\n";
}

void Level3::Close(Engine* game)
{

    std::cout << "Level3 Close" << std::endl;
}


void Level3::Pause()
{
    std::cout << "Level3 Paused" << std::endl;
}

void Level3::Resume()
{
    std::cout << "Level3 Resumed" << std::endl;
}



void Level3::Update(Engine* game)
{
    game->getCamera().UpdateCamera();
    FrameDelay(&m_fpslimiter, m_FPS);
    game->getWindow().Show_FPS_Inwindow(m_FPS);
    //Update screen
    fpsText = L"fps: " + std::to_wstring(int(m_FPS));

    for (int i = 0; i < 100; i++)
    {
        static std::mt19937 randEngine(static_cast<unsigned int>(time(nullptr)));
        static std::uniform_real_distribution<float> randAngle(0.0f, 360.0f);
        std::uniform_real_distribution<float> randX(-1200.0f, (float)game->getWindow().Get_Screen_Width() + 300);
        std::uniform_real_distribution<float> randY(-700.0f, (float)game->getWindow().Get_Screen_Height() + 100);
        std::uniform_real_distribution<float> color(0.0, 255);
        Vector2<float> pos(randX(randEngine), randY(randEngine));
        Color my_color( static_cast<GLubyte>(color(randEngine)), static_cast<GLubyte>(color(randEngine)), static_cast<GLubyte>(color(randEngine)), static_cast<GLubyte>(color(randEngine)));
        Vector2<float> vel(2.0f, 2.0f);

        if (game->getInputs().IsKeyPressed(SDL_SCANCODE_G))
        {
            m_ParticleBatch->addParticle(pos,  vel, my_color, 40.0f);
        }
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_UP))
    {
        Ani.Y += 4;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_DOWN))
    {
        Ani.Y -= 4;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_LEFT))
    {
        Ani.X -= 4;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_RIGHT))
    {
        Ani.X += 4;
    }
    if (game->getMouse().Is_Mouse_Clicked(MouseButton::Left))
    {
        game->ChangeState(Level2::Instance(), game);
    }
    if (game->getMouse().Is_Mouse_Clicked(MouseButton::Right))
    {
        game->ChangeState(Level1::Instance(), game);
    }

    game->getWindow().Swapbufferwindow();
}


void Level3::Draw(Engine* game)
{
    game->Update_Shaders();

    Text.Adding_Screen(game);
    Ani.Adding_Screen(game, true, 10);

    m_particleEngine.draw(&A);
    game->getShader().UnUseDisable();
}