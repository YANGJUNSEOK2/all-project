/************************************************************************
*	File name : SceneManager.h
*	Project name : apple
*   Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Control Scenes and scene state.
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include <memory>
#include <vector>
#include "IScene.h"
#include "LevelNum.h"
class [[nodiscard]] SceneManager
{
public:
    template<typename Level, typename... Args>
    void EmplaceScene(Args&&... arg) noexcept
    {
        mScenes.push_back(std::make_unique<Level>(std::forward<Args>(arg)...));
    }
    void Load() noexcept;
    void Update(double delta_time) noexcept;
    void SetNextScene(LevelNum level) noexcept;
    bool IsShutDown() noexcept;

private:
    enum class SceneState
    {
        Start,
        Load,
        Update,
        Unload,
        ShutDown,
        Exit,
    };

    std::vector<std::unique_ptr<IScene>> mScenes;
    IScene* mCurrentScene = nullptr;
    IScene* mNextScene = nullptr;

    SceneState mState = SceneState::Start;

    bool isShutDown = false;
};