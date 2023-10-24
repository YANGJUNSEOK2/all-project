/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:PlatformWindowGLFW.hpp
Project:Assignment2
Assignment name:OpenGLWindow
CourseNumber:cs230
Author:junseok.yang
Created:Spring 2019/3/22
------------------------------------------------------------------------*/
#pragma once
#include <CS230/window/OpenGLWindow.hpp>
#include <GLFW/glfw3.h>

namespace CS230
{
    class PlatformWindow {
    public:
       
        bool CreateAndShowWindow(const char* title, WindowEventHandler* event_handler,
            window::size desired_size = window::size{},
            OpenGLWindow::FullScreen start_fullscreen_as = OpenGLWindow::WINDOWED) noexcept;

        void PollEvents() noexcept;
        bool ShouldQuit() noexcept;
        void ShutDown() noexcept;
        void SwapBackBuffer() noexcept;

        void SetWindowTitle(const char* new_title) noexcept;
        void TurnOnMonitorVerticalSynchronization(bool enable) noexcept;
        bool IsMonitorVerticalSynchronizationOn() noexcept;

        bool IsFullScreen() noexcept;
        void ToggleFullScreen() noexcept;
        /*static void key_callback(GLFWwindow*window, int key, int scancode, int action, int mods);*/
        
        
    private:
        GLFWwindow* m_window;
        int xpos, ypos;
        int m_width;
        int m_height;
        /*inline static WindowEventHandler* m_EventHandler;*/
       
    };
}
