/************************************************************************
*	File name : Engine.cpp
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description :
*   All of things in Engine are singleton.
*   Relation of each parts are following.
*   Engine{Window{SceneManger and InputManager}}.
*   Init->Update->IsShutDown->ShutDown.
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include "Engine.h"
#include <iostream>

bool Engine::Init() noexcept
{
    logger->LogDebug("Engine Init");
    inputManager->Init();
    if (InitWindow(window) && InitSceneManager(sceneManager) && InitInputManager(inputManager) == true)
    {
        return true;
    }
    else
    {
        return false;
    }

}
void Engine::Update() noexcept
{
    while (window->Getwindow().isOpen())
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        double delta_time = std::chrono::duration<double>(now - lastTick).count();
        if (delta_time >= 1 / FPS)
        {
            lastTick = now;
        }
        window->UpdateEvent();
        sceneManager->Update(delta_time);
        inputManager->Update();
        inputManager->Init();
    }
    logger->LogDebug("Window Close");
    return;
}
void Engine::ShutDown() noexcept
{
    logger->LogDebug("Engine ShutDown");
}
bool Engine::IsGameEnd() noexcept
{
    return sceneManager->IsShutDown()||(!window->Getwindow().isOpen());
}

bool Engine::InitWindow(gsl::not_null<Window*> pWindow) noexcept
{
    pWindow->Init();
    return true;
}
bool Engine::InitSceneManager(gsl::not_null<SceneManager*> pScene) noexcept
{
    pScene->Load();
    return true;
}
bool Engine::InitInputManager(gsl::not_null<InputManager*> pInput) noexcept
{
    pInput->Init();
    return true;
}