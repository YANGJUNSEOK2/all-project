/************************************************************************
*	File name : SceneManager.cpp
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Control Scenes and scene state.
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include "SceneManager.h"
#include "IScene.h"
#include "Engine.h"
#include <iostream>

void SceneManager::Load() noexcept
{
    mState = SceneState::Start;
    mCurrentScene = mScenes[0].get();
}

void SceneManager::Update(double delta_time) noexcept
{
    switch (mState)
    {
    case SceneState::Start:
        mNextScene = mCurrentScene;
        mState = SceneState::Load;
        break;
    case SceneState::Load:
        mCurrentScene = mNextScene;
        Engine::LoggerIns().LogDebug("Load Level : " + mCurrentScene->GetName());
        if (mCurrentScene->Init() == true)
        {
            Engine::LoggerIns().LogDebug("Init Level success : " + mCurrentScene->GetName());
            mState = SceneState::Update;
            Engine::LoggerIns().LogDebug("Update Level : " + mCurrentScene->GetName());
        }
        else
        {
            Engine::LoggerIns().LogDebug("Load Level fail : " + mCurrentScene->GetName());
            mState = SceneState::Unload;
        }
        break;
    case SceneState::Update:
        if (mCurrentScene != mNextScene)
        {
            mState = SceneState::Unload;
        }
        else
        {
            mCurrentScene->Update(delta_time);
            mCurrentScene->Draw();
        }
        break;
    case SceneState::Unload:
        Engine::LoggerIns().LogDebug("Unload Level : " + mCurrentScene->GetName());
        mCurrentScene->ShutDown();
        if (mNextScene != nullptr)
        {
            mState = SceneState::Load;
        }
        else
        {
            Engine::LoggerIns().LogDebug("Unload failed : " + mCurrentScene->GetName());
            mState = SceneState::ShutDown;
        }
        break;
    case SceneState::ShutDown:
        Engine::LoggerIns().LogDebug("ShutDown Level : " + mCurrentScene->GetName());
        isShutDown = true;
        mState = SceneState::Exit;
        break;
    case SceneState::Exit:
        Engine::LoggerIns().LogDebug("Exit Level : " + mCurrentScene->GetName());
        break;
    }
}

bool SceneManager::IsShutDown() noexcept
{
    return isShutDown;
}

void SceneManager::SetNextScene(LevelNum level) noexcept
{
    mNextScene = mScenes[static_cast<int>(level)].get();
}