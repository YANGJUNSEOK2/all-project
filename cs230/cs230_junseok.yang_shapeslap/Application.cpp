/*
junseok.yang
shape_lap
cs230
spring 2019
Application.cpp
*/
#include "Application.hpp"
#include <CS230/graphics/GL.hpp>
#include <CS230/window/InputButtons.hpp>
#include <iostream>
#include <thread>

bool Application::StartUpWasSuccessful(std::string app_name, CS230::window::size window_dimensions)
{
    const auto window_is_setup = window.CreateAndShowWindow(app_name.c_str(), this, window_dimensions);
    if (!window_is_setup)
        return false;

    if (!window.IsMonitorVerticalSynchronizationOn())
        window.TurnOnMonitorVerticalSynchronization(true);

    CS230::GL::setup();

    if (!logic.StartUpWasSuccessful())
        return false;

    std::cout << "Application Controls:\n"
              << "\tEscape - Quit the Application\n"
              << "\tF - Toggle Fullscreen\n";

    timer.ResetTimeStamp();
    return true;
}

bool Application::ShouldClose() const { return window.ShouldQuit() || logic.ShouldClose(); }

void Application::Update()
{
    const auto delta_time_seconds = timer.GetElapsedSeconds();
    timer.ResetTimeStamp();

    logic.Update(delta_time_seconds);


    logic.Draw();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    window.SwapBackBuffer();

    window.PollEvents();
}

void Application::ShutDown()
{
    logic.ShutDown();
    window.ShutDown();
}

void Application::HandleKeyReleased(CS230::KeyboardButton button)
{
    switch (button)
    {
        case CS230::KeyboardButton::Escape:
            ShutDown();
            break;
        case CS230::KeyboardButton::F:
            window.ToggleFullScreen();
            break;
        default:
            break;
    }

    logic.HandleKeyReleased(button);
}

void Application::HandleMouseMove(int mouse_x, int mouse_y) { logic.HandleMouseMove(mouse_x, mouse_y); }

void Application::HandleResizeEvent(const CS230::window::size& frame_size) { logic.HandleResizeEvent(frame_size); }

void Application::HandleWindowClose() { ShutDown(); }
