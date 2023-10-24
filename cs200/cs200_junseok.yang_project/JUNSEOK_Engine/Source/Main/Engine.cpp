/************************************************************************
*	File name : Engine.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#include "../State/Level1.h"
#include "../State/Level2.h"
#include "Engine.h"
#include "../Shader/glCheck/glCheck.hpp"

void Engine::ChangeState(GameState* state, Engine* game)
{
    // cleanup the current state
    if (!states.empty()) {
        states.back()->Close(game);
        states.pop_back();
    }

    // store and init the new state
    states.push_back(state);
    states.back()->Init(game);
}

void Engine::PushState(GameState* state, Engine* game)
{
    // pause current state
    if (!states.empty()) {
        states.back()->Pause();
    }

    // store and init the new state
    states.push_back(state);
    states.back()->Init(game);
}

void Engine::PopState(Engine* game)
{
    // cleanup the current state
    if (!states.empty()) {
        states.back()->Close(game);
        states.pop_back();
    }

    // resume previous state
    if (!states.empty()) {
        states.back()->Resume();
    }
}

void Engine::Init(Engine* game)
{
    //Initialize SDL
    gameWindow.Init();
    InitShader();
}

void Engine::HandleEvents(Engine* game)
{
    // let the state handle events
    states.back()->HandleEvents(this);
}


void Engine::Update()
{
    // let the state update the game
    states.back()->Update(this);
}

void Engine::Draw()
{
    // let the state draw the screen
    states.back()->Draw(this);
}

void Engine::Close(Engine* game)
{
    while (!states.empty()) {
        states.back()->Close(game);
        states.pop_back();
    }

    // shutdown SDL
    SDL_Quit();
}

void Engine::Update_Shaders()
{
    glCheck(glClearDepth(1.0));
    glCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    m_ColorProgram.UseEnable();

    glCheck(glActiveTexture(GL_TEXTURE0));

    GLint textureLocation = m_ColorProgram.GetUniformLocation("shaderTexture");
    glCheck(glUniform1i(textureLocation, 0));

    GLuint pLocation = m_ColorProgram.GetUniformLocation("P");
    cameraMatrix = m_Camera.GetCameraOrtho();

    glCheck(glUniformMatrix3fv(pLocation, 1, GL_FALSE, &cameraMatrix.Elements[0][0]));
}

void Engine::InitShader()
{
    m_ColorProgram.CompileShaders("Source/Shader/colorShader.vert", "Source/Shader/colorShader.frag");
    m_ColorProgram.AddAttribute("vtPosition");
    m_ColorProgram.AddAttribute("vtColor");
    m_ColorProgram.AddAttribute("vtUV");
    m_ColorProgram.LinkShaders();
}


int main(int argc, char* args[])
{
    Engine game;
    //Start up SDL and create window
    game.Init(&game);

    game.ChangeState(Level1::Instance(), &game);

    //While application is running
    while (game.Running())
    {
        //Handle events on queue
        game.HandleEvents(&game);
        game.Draw();
        game.Update();
    }
    //Free resources and close SDL
    game.Close(&game);

    return 0;
}
