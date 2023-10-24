/************************************************************************
*	File name : Engine.h
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
#include <chrono>
#include "Window.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Logger.h"
#include <gsl/gsl>

class [[nodiscard]] Engine
{
public:
    Engine() = default;
    ~Engine() noexcept
    {
        delete inputManager;
        delete window;
        delete sceneManager;
        delete logger;
    }
    static Engine& EngineIns() noexcept { static Engine engine; return engine; }
    static Window& WindowIns() noexcept {
        return *EngineIns().window;
    }
    static SceneManager& SceneManagerIns() noexcept {
        return *EngineIns().sceneManager;
    }
    static InputManager& InputManagerIns() noexcept {
        return *EngineIns().inputManager;
    }
    static Logger& LoggerIns() noexcept {
        return *EngineIns().logger;
    }

    bool Init() noexcept;
    void Update() noexcept;
    void ShutDown() noexcept;
    bool IsGameEnd() noexcept;
    bool InitWindow(gsl::not_null<Window*> pWindow) noexcept;
    bool InitSceneManager(gsl::not_null<SceneManager*> pScene) noexcept;
    bool InitInputManager(gsl::not_null<InputManager*> pInput) noexcept;
private:
    gsl::owner<Window*> window = new Window{};
    gsl::owner<SceneManager*> sceneManager = new SceneManager{};
    gsl::owner<InputManager*> inputManager = new InputManager{};
#ifdef _DEBUG
    gsl::owner<Logger*> logger = new Logger(Logger::Severity::DEBUG, true);
#else
    gsl::owner<Logger*> logger = new Logger(Logger::Severity::EVENT, false);
#endif
    std::chrono::system_clock::time_point lastTick;
    double FPS = 60.0;
};