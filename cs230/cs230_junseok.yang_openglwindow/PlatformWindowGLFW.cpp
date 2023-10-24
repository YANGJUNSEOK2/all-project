/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:PlatformWindowGLFW.cpp
Project:Assignment2
Assignment name:OpenGLWindow
CourseNumber:cs230
Author:junseok.yang
Created:Spring 2019/3/22
------------------------------------------------------------------------*/

#include "PlatformWindowGLFW.hpp"
#include <CS230/window/InputButtons.hpp>
#include <CS230/window/WindowEventHandler.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace
{
    CS230::WindowEventHandler* m_EventHandler;
    CS230::WindowEventHandler* windowClose;

    void window_close_callback(GLFWwindow* /*window*/)
    {
        windowClose->HandleWindowClose();
    }
    void window_size_callback(GLFWwindow* window, int width, int height)
    {
        (window);

        CS230::window::size m_desired_size;

        m_desired_size.width = width;
        m_desired_size.height = height;

        m_EventHandler->HandleResizeEvent(m_desired_size);
    }
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        (xoffset);

        if (window)
        {
            m_EventHandler->HandleMouseWheelScroll(int(yoffset));
        }

    }
    void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        glfwGetCursorPos(window, &xpos, &ypos);

        m_EventHandler->HandleMouseMove(int(xpos), int(ypos));

    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        (window);
        (mods);

        if (action == GLFW_PRESS)
        {
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_LEFT:
                m_EventHandler->HandleMouseButtonPress(CS230::MouseButton::Left);
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                m_EventHandler->HandleMouseButtonPress(CS230::MouseButton::Right);
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                m_EventHandler->HandleMouseButtonPress(CS230::MouseButton::Middle);
                break;
            default:
                m_EventHandler->HandleMouseButtonPress(CS230::MouseButton::None);
                break;
            }
        }
        if (action == GLFW_RELEASE)
        {
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_LEFT:
                m_EventHandler->HandleMouseButtonReleased(CS230::MouseButton::Left);
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                m_EventHandler->HandleMouseButtonReleased(CS230::MouseButton::Right);
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                m_EventHandler->HandleMouseButtonReleased(CS230::MouseButton::Middle);
                break;
            default:
                m_EventHandler->HandleMouseButtonReleased(CS230::MouseButton::None);
                break;
            }
        }
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        (window);
        (scancode);
        (mods);

        if (action == GLFW_PRESS)
        {
            switch (key)
            {
            case GLFW_KEY_ESCAPE:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::Escape);
                break;
            case GLFW_KEY_SPACE:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::Space);
                break;
            case GLFW_KEY_LEFT:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::Left);
                break;
            case GLFW_KEY_RIGHT:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::Right);
                break;
            case GLFW_KEY_UP:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::Up);
                break;
            case GLFW_KEY_DOWN:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::Down);
                break;
            case GLFW_KEY_0:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::_0);
                break;
            case GLFW_KEY_1:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::_1);
                break;
            case GLFW_KEY_2:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::_2);
                break;
            case GLFW_KEY_3:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::_3);
                break;
            case GLFW_KEY_4:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::_4);
                break;
            case GLFW_KEY_5:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::_5);
                break;
            case GLFW_KEY_6:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::_6);
                break;
            case GLFW_KEY_7:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::_7);
                break;
            case GLFW_KEY_8:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::_8);
                break;
            case GLFW_KEY_9:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::_9);
                break;
            case GLFW_KEY_KP_0:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::NumPad_0);
                break;
            case GLFW_KEY_KP_1:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::NumPad_1);
                break;
            case GLFW_KEY_KP_2:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::NumPad_2);
                break;
            case GLFW_KEY_KP_3:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::NumPad_3);
                break;
            case GLFW_KEY_KP_4:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::NumPad_4);
                break;
            case GLFW_KEY_KP_5:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::NumPad_5);
                break;
            case GLFW_KEY_KP_6:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::NumPad_6);
                break;
            case GLFW_KEY_KP_7:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::NumPad_7);
                break;
            case GLFW_KEY_KP_8:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::NumPad_8);
                break;
            case GLFW_KEY_KP_9:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::NumPad_9);
                break;
            case GLFW_KEY_Q:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::Q);
                break;
            case GLFW_KEY_A:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::A);
                break;
            case GLFW_KEY_Z:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::Z);
                break;
            case GLFW_KEY_W:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::W);
                break;
            case GLFW_KEY_S:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::S);
                break;
            case GLFW_KEY_X:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::X);
                break;
            case GLFW_KEY_E:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::E);
                break;
            case GLFW_KEY_D:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::D);
                break;
            case GLFW_KEY_C:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::C);
                break;
            case GLFW_KEY_R:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::R);
                break;
            case GLFW_KEY_F:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::F);
                break;
            case GLFW_KEY_V:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::V);
                break;
            case GLFW_KEY_T:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::T);
                break;
            case GLFW_KEY_G:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::G);
                break;
            case GLFW_KEY_B:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::B);
                break;
            case GLFW_KEY_Y:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::Y);
                break;
            case GLFW_KEY_H:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::H);
                break;
            case GLFW_KEY_N:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::N);
                break;
            case GLFW_KEY_U:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::U);
                break;
            case GLFW_KEY_J:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::J);
                break;
            case GLFW_KEY_M:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::M);
                break;
            case GLFW_KEY_I:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::I);
                break;
            case GLFW_KEY_K:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::K);
                break;
            case GLFW_KEY_O:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::O);
                break;
            case GLFW_KEY_L:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::L);
                break;
            case GLFW_KEY_P:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::P);
                break;
            default:
                m_EventHandler->HandleKeyPress(CS230::KeyboardButton::None);
                break;
            }
        }

        if (action == GLFW_RELEASE)
        {
            switch (key)
            {
            case GLFW_KEY_ESCAPE:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::Escape);
                break;
            case GLFW_KEY_SPACE:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::Space);
                break;
            case GLFW_KEY_LEFT:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::Left);
                break;
            case GLFW_KEY_RIGHT:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::Right);
                break;
            case GLFW_KEY_UP:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::Up);
                break;
            case GLFW_KEY_DOWN:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::Down);
                break;
            case GLFW_KEY_0:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::_0);
                break;
            case GLFW_KEY_1:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::_1);
                break;
            case GLFW_KEY_2:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::_2);
                break;
            case GLFW_KEY_3:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::_3);
                break;
            case GLFW_KEY_4:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::_4);
                break;
            case GLFW_KEY_5:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::_5);
                break;
            case GLFW_KEY_6:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::_6);
                break;
            case GLFW_KEY_7:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::_7);
                break;
            case GLFW_KEY_8:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::_8);
                break;
            case GLFW_KEY_9:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::_9);
                break;
            case GLFW_KEY_KP_0:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::NumPad_0);
                break;
            case GLFW_KEY_KP_1:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::NumPad_1);
                break;
            case GLFW_KEY_KP_2:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::NumPad_2);
                break;
            case GLFW_KEY_KP_3:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::NumPad_3);
                break;
            case GLFW_KEY_KP_4:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::NumPad_4);
                break;
            case GLFW_KEY_KP_5:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::NumPad_5);
                break;
            case GLFW_KEY_KP_6:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::NumPad_6);
                break;
            case GLFW_KEY_KP_7:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::NumPad_7);
                break;
            case GLFW_KEY_KP_8:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::NumPad_8);
                break;
            case GLFW_KEY_KP_9:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::NumPad_9);
                break;
            case GLFW_KEY_Q:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::Q);
                break;
            case GLFW_KEY_A:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::A);
                break;
            case GLFW_KEY_Z:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::Z);
                break;
            case GLFW_KEY_W:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::W);
                break;
            case GLFW_KEY_S:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::S);
                break;
            case GLFW_KEY_X:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::X);
                break;
            case GLFW_KEY_E:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::E);
                break;
            case GLFW_KEY_D:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::D);
                break;
            case GLFW_KEY_C:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::C);
                break;
            case GLFW_KEY_R:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::R);
                break;
            case GLFW_KEY_F:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::F);
                break;
            case GLFW_KEY_V:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::V);
                break;
            case GLFW_KEY_T:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::T);
                break;
            case GLFW_KEY_G:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::G);
                break;
            case GLFW_KEY_B:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::B);
                break;
            case GLFW_KEY_Y:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::Y);
                break;
            case GLFW_KEY_H:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::H);
                break;
            case GLFW_KEY_N:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::N);
                break;
            case GLFW_KEY_U:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::U);
                break;
            case GLFW_KEY_J:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::J);
                break;
            case GLFW_KEY_M:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::M);
                break;
            case GLFW_KEY_I:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::I);
                break;
            case GLFW_KEY_K:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::K);
                break;
            case GLFW_KEY_O:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::O);
                break;
            case GLFW_KEY_L:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::L);
                break;
            case GLFW_KEY_P:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::P);
                break;
            default:
                m_EventHandler->HandleKeyReleased(CS230::KeyboardButton::None);
                break;
            }
        }

    }
}


namespace CS230
{

    bool verticalSync;

    bool PlatformWindow::CreateAndShowWindow(const char* title, WindowEventHandler* event_handler, window::size desired_size, OpenGLWindow::FullScreen start_fullscreen_as) noexcept
    {
        
        m_width = desired_size.width =700;
        m_height = desired_size.height =400;
        
        if (!glfwInit())
        {
            return false;
        }

        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GLFW_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_RED_BITS, 8);
        glfwWindowHint(GLFW_GREEN_BITS, 8);
        glfwWindowHint(GLFW_BLUE_BITS, 8);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
        
        m_window = glfwCreateWindow(desired_size.width, desired_size.height, title, nullptr, nullptr);

        if (!m_window)
        {
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_window);

        TurnOnMonitorVerticalSynchronization(IsMonitorVerticalSynchronizationOn());

        GLenum err = glewInit();
        if (err)
        {
            std::cerr << "GLEW error: " << glewGetErrorString(err);
        }

        m_EventHandler = event_handler;
        
        int action = 0;
        if (start_fullscreen_as == OpenGLWindow::FULLSCREEN)
        {
            if(action==GLFW_PRESS)
            ToggleFullScreen();
            m_EventHandler->HandleResizeEvent(desired_size);
        }
        else if (start_fullscreen_as == OpenGLWindow::WINDOWED)
        {
            if (action == GLFW_PRESS)
                ToggleFullScreen();
        }
       
        m_EventHandler->HandleResizeEvent(desired_size);

        windowClose = event_handler;

        glfwSetWindowCloseCallback(m_window, window_close_callback);
        glfwSetWindowSizeCallback(m_window, window_size_callback);
        glfwSetCursorPosCallback(m_window, cursor_position_callback);
        glfwSetKeyCallback(m_window, key_callback);
        glfwSetMouseButtonCallback(m_window, mouse_button_callback);
        glfwSetScrollCallback(m_window, scroll_callback);

        return true;

    }

    void PlatformWindow::PollEvents() noexcept
    {
        glfwPollEvents();
    }

    bool PlatformWindow::ShouldQuit() noexcept
    {
        return glfwWindowShouldClose(m_window);
    }

    void PlatformWindow::ShutDown() noexcept
    {
        glfwSetWindowCloseCallback(m_window, window_close_callback);
    }

    void PlatformWindow::SwapBackBuffer() noexcept
    {
        glfwSwapBuffers(m_window);
    }

    void PlatformWindow::SetWindowTitle(const char* new_title) noexcept
    {
        glfwSetWindowTitle(m_window, new_title);
    }

    void PlatformWindow::TurnOnMonitorVerticalSynchronization(bool enable) noexcept
    {
        verticalSync = enable;
        glfwSwapInterval(verticalSync);
    }

    bool PlatformWindow::IsMonitorVerticalSynchronizationOn() noexcept
    {
        return verticalSync;
    }

    bool PlatformWindow::IsFullScreen() noexcept
    {
            return glfwGetWindowMonitor(m_window);    
    }

    void PlatformWindow::ToggleFullScreen() noexcept
    {
        const GLFWvidmode* m_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        GLFWmonitor* m_monitor = glfwGetPrimaryMonitor();

        if (IsFullScreen() == false)
        {
            glfwGetWindowPos(m_window, &xpos, &ypos);
            glfwGetWindowSize(m_window, &m_width, &m_height);
            glfwSetWindowMonitor(m_window, m_monitor, xpos, ypos, m_mode->width, m_mode->height, 0);
            glViewport(0, 0, m_mode->width, m_mode->height);
            TurnOnMonitorVerticalSynchronization(verticalSync);
        }
        else
        {
            glfwSetWindowMonitor(m_window, nullptr, xpos, ypos, m_width, m_height, 0);
            glViewport(0, 0, m_width, m_height);
        }
    }
}