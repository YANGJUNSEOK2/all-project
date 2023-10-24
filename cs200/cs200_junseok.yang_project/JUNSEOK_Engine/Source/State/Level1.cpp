/************************************************************************
*	File name : Level1.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#include "Level1.h"
#include "Level2.h"

Level1 Level1::m_Level1;


void Level1::Init(Engine* game)
{
    game->getWindow().Change_Window_Color({ 255, 255, 180, 255 });
    m_Mesh.Init();
    std::cout << "Level1 Init" << std::endl;
    m_MaxFPS = 60.f;
    m_fpslimiter.Init(m_MaxFPS);

    std::cout
        << "==============LEVEL1 ======================================\n"
        << "==============WINDOW ======================================\n"
        << "==============WINDOW VSYNC -> V============================\n"
        << "==============WINDOW FULL SCREEN -> F======================\n"
        << "==============WINDOW RESIZE -> MOUSE=======================\n"
        << "==============WINDOW CLOSE -> ESC==========================\n"
        << "==============WINDOW FOCUS -> MOUSE LEFT CLICK=============\n"
        << "==============CAMERA ======================================\n"
        << "==============CAMERA TRANSLATION W A S D===================\n"
        << "==============CAMERA ROTATION Q E =========================\n"
        << "==============CAMERA  ZOOM MOUSE WHEEL=====================\n"
        << "==============MESH ========================================\n"
        << "==============MESH MOVE -> KP_4568=========================\n"
        << "==============MESH ROTATION -> KP_7========================\n"
        << "==============MESH SCALE -> KP_12==========================\n"
        << "==============HIERARCHICAL=================================\n"
        << "==============HIERARCHICAL MOVE -> LEFT RIGHT DOWN UP======\n"
        << "==============HIERARCHICAL ROTATION -> I===================\n"
        << "==============HIERARCHICAL SCALE -> O P====================\n"
        << "===========================================================\n"
        << "==============LEVEL2 -> MOUSE RIGHT CLICK==================\n";

    game->getCamera().InitCamera(game->getWindow().Get_Screen_Width(), game->getWindow().Get_Screen_Height());
}

void Level1::Close(Engine* game)
{
    std::cout << "Level1 Close" << std::endl;
    m_Mesh.Dispose();
}

void Level1::Pause()
{
    std::cout << "Level1 Paused" << std::endl;
}

void Level1::Resume()
{
    std::cout << "Level1 Resumed" << std::endl;
}

void Level1::Update(Engine* game)
{
    game->getCamera().UpdateCamera();
    FrameDelay(&m_fpslimiter, m_FPS);
    game->getWindow().Show_FPS_Inwindow(m_FPS);

    //Hierarchical = m_BoxPosition * m_BoxAngle * m_BoxWH * m_Box2Position * m_Box2Angle * m_Box2WH;

    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_RIGHT))
    {
        m_BoxPosition.Column[2].x += 5.f;
        m_Box2Position.Column[2].x += 10.f;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_LEFT))
    {
        m_BoxPosition.Column[2].x -= 5;
        m_Box2Position.Column[2].x -= 10.f;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_DOWN))
    {
        m_BoxPosition.Column[2].y -= 5;
        m_Box2Position.Column[2].y -= 10.f;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_UP))
    {
        m_BoxPosition.Column[2].y += 5;
        m_Box2Position.Column[2].y += 10.f;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_O))
    {
        m_BoxWH.Column[0].x += 5;
        m_BoxWH.Column[1].y += 5;
        m_Box2WH.Column[0].x += 10;
        m_Box2WH.Column[1].y += 10;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_P))
    {
        m_BoxWH.Column[0].x -= 5;
        m_BoxWH.Column[1].y -= 5;
        m_Box2WH.Column[0].x -= 10;
        m_Box2WH.Column[1].y -= 10;
    }
    if(game->getInputs().IsKeyPressed(SDL_SCANCODE_KP_4))
    {
        m_BoxPosition.Column[2].x -= 5;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_KP_5))
    {
        m_BoxPosition.Column[2].y -= 5;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_KP_6))
    {
        m_BoxPosition.Column[2].x += 5.f;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_KP_7))
    {
        m_BoxAngle.Column[0].x += PI / 100.0f;
        m_BoxAngle.Column[1].y += PI / 100.0f;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_KP_8))
    {
        m_BoxPosition.Column[2].y += 5;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_KP_1))
    {
        m_BoxWH.Column[0].x += 5;
        m_BoxWH.Column[1].y += 5;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_KP_2))
    {
        m_BoxWH.Column[0].x -= 5;
        m_BoxWH.Column[1].y -= 5;
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_W))
    {
        game->getCamera().CameraTranslation(0, -5);
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_S))
    {
        game->getCamera().CameraTranslation(0, 5);
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_A))
    {
        game->getCamera().CameraTranslation(5, 0);
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_D))
    {
        game->getCamera().CameraTranslation(-5, 0);
    }
    if (game->getInputs().IsKeyPressed(SDL_SCANCODE_Q))
    {
        cameraRotateDirection = 1;
    }//camera rotate
    else if (game->getInputs().IsKeyPressed(SDL_SCANCODE_E))
    {
        cameraRotateDirection = -1;
    }//camera rotate
    else if (game->getInputs().IsKeyReleased(SDL_SCANCODE_Q))
    {
        cameraRotateDirection = 0;
    }//camera stop
    else if (game->getInputs().IsKeyReleased(SDL_SCANCODE_E))
    {
        cameraRotateDirection = 0;
    }//camera stop
    if(game->getInputs().IsKeyPressed(SDL_SCANCODE_I))
    {
        m_BoxAngle.Column[0].x += PI / 100.0f;
        m_BoxAngle.Column[1].y += PI / 100.0f;
        m_Box2Angle.Column[0].x += PI / 10.0f;
        m_Box2Angle.Column[1].y += PI / 10.0f;
    }
    game->getCamera().CameraRotation(cameraRotateDirection * radians_per_second);
    if (game->getMouse().Is_Mouse_Clicked(MouseButton::Right))
    {
        game->ChangeState(Level2::Instance(), game);
    }

    if(game->getMouse().Is_Mouse_Clicked(MouseButton::Left))
    {
        game->getWindow().show_focus(1556);
    }
}

void Level1::Draw(Engine* game)
{ 
    game->Update_Shaders();
    game->getShader().UseEnable();

    game->getShader().UnUseDisable();


    m_Mesh.DrawLine(Vector2<float>{-3000.f, 0.f}, { 3000.f, 0.f }, Color{ 0,0,0,255 });
    m_Mesh.End();
    m_Mesh.Render_Lines(game->getCameraMatrix(), 2.0f);

    m_Mesh.DrawLine({ 0.f,-3000.f }, { 0.f,3000.f }, Color{ 0,0,0,255 });
    m_Mesh.End();
    m_Mesh.Render_Lines(game->getCameraMatrix(), 2.0f);

    m_Mesh.DrawBox({ m_BoxPosition.Column[2].x, m_BoxPosition.Column[2].y, m_BoxWH.Column[0].x, m_BoxWH.Column[1].y }, Color{ 255,0,0,255 }, m_BoxAngle.Column[0].x);
    m_Mesh.End();
    m_Mesh.Render_TRIANGLE_FAN(game->getCameraMatrix());

    m_Mesh.DrawBox(Vector4<float>{m_Box2Position.Column[2].x, m_Box2Position.Column[2].y, m_Box2WH.Column[0].x, m_Box2WH.Column[1].y}, Color{ 255,0,0,255 }, m_Box2Angle.Column[0].x);
    m_Mesh.End();
    m_Mesh.Render_Lines(game->getCameraMatrix(), 3.0);

    m_Mesh.DrawCircle({ m_CirclePosition.Column[2].x, m_CirclePosition.Column[2].y}, { m_CircleWH.Column[0].x,m_CircleWH.Column[1].y }, { 0,255,0,255 });
    m_Mesh.End();
    m_Mesh.Render_TRIANGLE_FAN(game->getCameraMatrix());

    m_Mesh.DrawCircle(Vector2<float>{m_Circle2Position.Column[2].x, m_Circle2Position.Column[2].y}, { m_Circle2WH.Column[0].x, m_Circle2WH.Column[1].y }, Color{ 200,0,200,255 });
    m_Mesh.End();
    m_Mesh.Render_Lines(game->getCameraMatrix(),2.0f);

    m_Mesh.DrawTriangle(Vector2<float>{m_TrianglePosition.Column[2].x, m_TrianglePosition.Column[2].y},{ m_TriangleWH.Column[0].x, m_TriangleWH.Column[1].y }, Color{ 100,200,0,255 });
    m_Mesh.End();        
    m_Mesh.Render_TRIANGLE_FAN(game->getCameraMatrix());

    m_Mesh.DrawTriangle(Vector2<float>{m_Triangle2Position.Column[2].x, m_Triangle2Position.Column[2].y},{ m_Triangle2WH.Column[0].x, m_Triangle2WH.Column[1].y }, Color{ 200,100,100,255 });
    m_Mesh.End();
    m_Mesh.Render_Lines(game->getCameraMatrix(), 2.0f);

    m_Mesh.DrawLine(Vector2<float>{m_LinePosition.Column[2].x, m_LinePosition.Column[2].y}, { m_LineWH.Column[0].x, m_LineWH.Column[1].y }, Color{ 0,0,255,255 });
    m_Mesh.End();
    m_Mesh.Render_Lines(game->getCameraMatrix(), 3.0f);

    game->getWindow().Swapbufferwindow();
}
