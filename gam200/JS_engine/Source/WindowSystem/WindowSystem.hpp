#pragma once
#include <iostream>
#include <../../Source/MathLibrary/MathLibrary.hpp>
#include <glew.h>
#include <glfw3.h>
#include <bitset>

namespace JS_Engine {
    namespace WindowSystem {
#define MaxKeyboard 1024
#define MaxMouse    32
        class Window {
        public:
            Window(const char *p_GameTitle, int p_WindowWidth, int p_WindowHeight);
            ~Window();
            //Update Window
            void UpdateWindow();
            //Clear Window
            void ClearWindow() const;
            //Get Width of Window
            inline int GetWindowWidth() const { return m_WindowWidth; }
            //Get Height of Window
            inline int GetWindowHeight() const { return m_WindowHeight; }
            //Check If Window Closed
            bool IsWindowClosed() const;
            //Check If Keyboard Is Pressed
            bool IsKeyboardPressed(unsigned int p_KeyboardInput) const;
            //Check If Mouse Is Pressed
            bool IsMousePressed(unsigned int p_MouseInput) const;
            //Get Mouse Position
            void GetMousePosition(double &p_XPosition, double &p_YPosition) const;
        private:
            const char *m_GameTitle;
            int			m_WindowWidth;
            int			m_WindowHeight;
            bool		m_WindowClosed;
            bool		m_Keyboard[MaxKeyboard];
            bool		m_Mouse[MaxMouse];
            double		m_XPosition;
            double		m_YPosition;
            GLFWwindow *m_GameWindow;
            //Initialize Window
            bool Initialize();
            //Keyboard Callback
            friend static void KeyboardCallback(GLFWwindow *p_GameWindow, int p_KeyboardInput, int p_ScanCode, int p_Action, int p_Mods);
            //Mouse Callback
            friend static void MouseCallback(GLFWwindow *p_GameWindow, int p_MouseInput, int p_Action, int p_Mods);
            //Cursor Position Callback
            friend static void CursorPositionCallback(GLFWwindow *p_GameWindow, double p_XPosition, double p_YPosition);
        };
    }
}