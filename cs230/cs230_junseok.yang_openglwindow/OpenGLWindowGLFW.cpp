/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:OpenGLWindowGLFW.cpp
Project:Assignment2
Assignment name:OpenGLWindow
CourseNumber:cs230
Author:junseok.yang
Created:Spring 2019/3/22
------------------------------------------------------------------------*/
#include "PlatformWindowGLFW.hpp"
#include <CS230/window/OpenGLWindow.hpp>


namespace CS230
{
    OpenGLWindow::OpenGLWindow() noexcept :
        platformWindow(std::make_unique<PlatformWindow>())
    { }

    OpenGLWindow::~OpenGLWindow() noexcept { }

    bool OpenGLWindow::CreateAndShowWindow(const char* title, WindowEventHandler* event_handler,
        window::size desired_size,
        FullScreen start_fullscreen_as) const noexcept
    {
        return platformWindow->CreateAndShowWindow(title,event_handler,desired_size,start_fullscreen_as);
    }

    void OpenGLWindow::PollEvents() const noexcept
    {
        platformWindow->PollEvents();
    }

    bool OpenGLWindow::ShouldQuit() const noexcept
    {
        return platformWindow->ShouldQuit();
    }

    void OpenGLWindow::ShutDown() const noexcept
    {
        platformWindow->ShutDown();
    }

    void OpenGLWindow::SwapBackBuffer() const noexcept
    {
        platformWindow->SwapBackBuffer();
    }

    void OpenGLWindow::SetWindowTitle(const char* new_title) const noexcept
    {
        platformWindow->SetWindowTitle(new_title);
    }
   
    void OpenGLWindow::TurnOnMonitorVerticalSynchronization(bool enable) const noexcept
    {
        platformWindow->TurnOnMonitorVerticalSynchronization(enable);
    }
    
    bool OpenGLWindow::IsMonitorVerticalSynchronizationOn() const noexcept
    {
        return platformWindow->IsMonitorVerticalSynchronizationOn();
    }

    bool OpenGLWindow::IsFullScreen() const noexcept
    {
        return platformWindow->IsFullScreen();
    }

    void OpenGLWindow::ToggleFullScreen() const noexcept
    {
        platformWindow->ToggleFullScreen();
    }

}
