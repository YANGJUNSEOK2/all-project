#include "WindowSystem.hpp"
#include "../Input/InputEventHandler.hpp"
#include "../Input/InputButton.hpp"

namespace JS_Engine {
    namespace WindowSystem {

        void WindowResize(GLFWwindow *p_GameWindow, int p_WindowWidth, int p_WindowHeight);
        void KeyboardCallback(GLFWwindow *p_GameWindow, int p_KeyboardInut, int p_ScanCode, int p_Action, int p_Mods);
        void MouseCallback(GLFWwindow *p_GameWindow, int p_MouseInput, int p_Action, int p_Mods);
        void CursorPositionCallback(GLFWwindow *p_GameWindow, double p_XPosition, double p_YPosition);

        Window::Window(const char *p_GameTitle, int p_WindowWidth, int p_WindowHeight) {
            m_GameTitle = p_GameTitle;
            m_WindowWidth = p_WindowWidth;
            m_WindowHeight = p_WindowHeight;

            if (!Initialize()) {
                glfwTerminate();
            }
            for (int i = 0; i < MaxKeyboard; i++) {
                m_Keyboard[i] = false;
            }
            for (int i = 0; i < MaxMouse; i++) {
                m_Mouse[i] = false;
            }
        }

        Window::~Window() {
            glfwTerminate();
        }

        void Window::UpdateWindow() {
            GLenum OpenGLError = glGetError();
            if (OpenGLError != GL_NO_ERROR) {
                std::cout << "[ERROR] OPENGL ERROR: " << OpenGLError << std::endl;
            }
            glfwPollEvents();
            glfwSwapBuffers(m_GameWindow);
        }

        void Window::ClearWindow() const {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        bool Window::IsWindowClosed() const {
            return glfwWindowShouldClose(m_GameWindow) == 1;
        }

        bool Window::IsKeyboardPressed(unsigned int p_KeyboardInput) const {
            if (p_KeyboardInput >= MaxKeyboard) {
                return false;
            }
            return m_Keyboard[p_KeyboardInput];
        }

        bool Window::IsMousePressed(unsigned int p_MouseInput) const {
            if (p_MouseInput >= MaxMouse) {
                return false;
            }
            return m_Mouse[p_MouseInput];
        }

        void Window::GetMousePosition(double &p_XPosition, double &p_YPosition) const {
            p_XPosition = m_XPosition;
            p_YPosition = m_YPosition;
        }

        bool Window::Initialize() {
            if (!glfwInit()) {
                std::cout << "[ERROR] GLFW INITIALIZE FAILED" << std::endl;
                return false;
            }
            m_GameWindow = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_GameTitle, NULL, NULL);
            if (!m_GameWindow) {
                std::cout << "[ERROR] GAME WINDOW INITIALIZE FAILED" << std::endl;
                return false;
            }
            glfwMakeContextCurrent(m_GameWindow);
            glfwSetWindowUserPointer(m_GameWindow, this);
            glfwSetWindowSizeCallback(m_GameWindow, WindowResize);
            glfwSetKeyCallback(m_GameWindow, KeyboardCallback);
            glfwSetMouseButtonCallback(m_GameWindow, MouseCallback);
            glfwSetCursorPosCallback(m_GameWindow, CursorPositionCallback);
            glfwSwapInterval(0);

            if (glewInit() != GLEW_OK) {
                std::cout << "[ERROR] GLEW INITIALIZE FAILED" << std::endl;
                return false;
            }
            std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
            return true;
        }

        void WindowResize(GLFWwindow *p_GameWindow, int p_WindowWidth, int p_WindowHeight) {
            glViewport(0, 0, p_WindowWidth, p_WindowHeight);
        }

        void KeyboardCallback(GLFWwindow *p_GameWindow, int p_KeyboardInput, int p_ScanCode, int p_Action, int p_Mods) {
            Window *WindowPointer = (Window*)glfwGetWindowUserPointer(p_GameWindow);
            WindowPointer->m_Keyboard[p_KeyboardInput] = p_Action != GLFW_RELEASE;
        }

        void MouseCallback(GLFWwindow *p_GameWindow, int p_MouseInput, int p_Action, int p_Mods) {
            Window *WindowPointer = (Window*)glfwGetWindowUserPointer(p_GameWindow);
            WindowPointer->m_Mouse[p_MouseInput] = p_Action != GLFW_RELEASE;
        }

        void CursorPositionCallback(GLFWwindow *p_GameWindow, double p_XPosition, double p_YPosition) {
            Window *WindowPointer = (Window*)glfwGetWindowUserPointer(p_GameWindow);
            WindowPointer->m_XPosition = p_XPosition;
            WindowPointer->m_YPosition = p_YPosition;
        }

       //std::bitset<MaxKeyboard> m_KeyPressed;
       //std::bitset<MaxKeyboard> m_KeyTriggered;
       //std::bitset<MaxKeyboard> m_KeyReleased;
       //MathLibrary::Vector2 m_Position;
       //std::bitset<MaxMouse> m_MousePressed;
       //std::bitset<MaxMouse> m_MouseTriggered;
       //std::bitset<MaxMouse> m_MouseDoubleClick;
       //std::bitset<MaxMouse> m_MouseReleased;

       // JS_Engine::Input::InputEventHandler* p_EventHandler;
       // 
       // void WindowResize(GLFWwindow *p_GameWindow, int p_WindowWidth, int p_WindowHeight);
       // void KeyboardCallback(GLFWwindow *p_GameWindow, int p_KeyboardInut, int p_ScanCode, int p_Action, int p_Mods);
       // void MouseCallback(GLFWwindow *p_GameWindow, int p_MouseInput, int p_Action, int p_Mods);
       // void CursorPositionCallback(GLFWwindow *p_GameWindow, double p_XPosition, double p_YPosition);
       //
       // Window::Window(const char *p_GameTitle, int p_WindowWidth, int p_WindowHeight) {
       //     m_GameTitle = p_GameTitle;
       //     m_WindowWidth = p_WindowWidth;
       //     m_WindowHeight = p_WindowHeight;

       //     if (!Initialize()) {
       //         glfwTerminate();
       //     }
       //     for (int i = 0; i < MaxKeyboard; i++) {
       //         m_Keyboard[i] = false;
       //     }
       //     for (int i = 0; i < MaxMouse; i++) {
       //         m_Mouse[i] = false;
       //     }
       // }
       // 
       // Window::~Window() {
       //     glfwTerminate();
       // }
       // 
       // void Window::UpdateWindow() {
       //     glfwPollEvents();
       //     glfwSwapBuffers(m_GameWindow);
       // }
       //
       // void Window::ClearWindow() const {
       //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       // }
       //
       // bool Window::IsWindowClosed() const {
       //     return glfwWindowShouldClose(m_GameWindow) == 1;
       // }
       // 
       // bool Window::IsKeyboardPressed(unsigned int p_KeyboardInput) const{
       //     if (p_KeyboardInput >= MaxKeyboard) {
       //         return false;
       //     }
       //     return m_Keyboard[p_KeyboardInput];
       // }
       // //키가 눌리는 dt 시간이 1번 나오게 만든다
       // 
       // //bool Window::IsKeyboardTriggered(unsigned p_KeyboardInput) const
       // //{
       // //    if (p_KeyboardInput >= MaxKeyboard) {
       // //        return false;
       // //    }
       // //    return m_KeyTriggered[p_KeyboardInput];
       // //}
       //
       // //bool Window::IsKeyboardReleased(unsigned p_KeyboardInput) const
       // //{
       // //    if (p_KeyboardInput >= MaxKeyboard) {
       // //        return false;
       // //    }
       // //    return m_KeyReleased[p_KeyboardInput];
       // //}
       // //이건 필요 없을 가능성 99퍼 (이미 콜백으로 만들었음)
       //
       ////void Window::SetKeyPressed(unsigned p_KeyboardInput, unsigned p_KeyType)
       ////{
       ////    if (p_KeyType == GLFW_PRESS)
       ////    {
       ////        m_KeyPressed.set(p_KeyboardInput);
       ////        m_KeyTriggered.set(p_KeyboardInput);
       ////    }
       ////    else if (p_KeyType == GLFW_RELEASE)
       ////    {
       ////        m_KeyReleased.set(p_KeyboardInput);
       ////        m_KeyPressed.reset(p_KeyboardInput);
       ////    }
       ////}
       ////
       //
       // bool Window::IsMousePressed(unsigned int p_MouseInput) const{
       //     if (p_MouseInput >= MaxMouse) {
       //         return false;
       //     }
       //     return m_Mouse[p_MouseInput];
       // }
       // //키가 눌리는 dt 시간이 1번 나오게 만든다
       // 
       // //bool Window::IsMouseTriggered(unsigned p_MouseInput) const
       // //{
       // //    if (p_MouseInput >= MaxMouse) {
       // //        return false;
       // //    }
       // //    return m_MouseTriggered[p_MouseInput];
       // //}
       // 
       // //bool Window::IsMouseReleased(unsigned p_MouseInput) const
       // //{
       // //    if (p_MouseInput >= MaxMouse) {
       // //        return false;
       // //    }
       // //    return m_MouseReleased[p_MouseInput];
       // //}

       //
       // void Window::GetMousePosition(double &p_XPosition, double &p_YPosition) const {
       //     p_XPosition = m_XPosition;
       //     p_YPosition = m_YPosition;
       // }
       // 
       // bool Window::Initialize() {
       //     if (!glfwInit()) {
       //         std::cout << "[ERROR] GLFW INITIALIZE FAILED" << std::endl;
       //         return false;
       //     }
       //     m_GameWindow = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_GameTitle, NULL, NULL);
       //     if (!m_GameWindow) {
       //         std::cout << "[ERROR] GAME WINDOW INITIALIZE FAILED" << std::endl;
       //         return false;
       //     }
       //     glfwMakeContextCurrent(m_GameWindow);
       //     glfwSetWindowUserPointer(m_GameWindow, this);
       //     glfwSetWindowSizeCallback(m_GameWindow, WindowResize);
       //     glfwSetKeyCallback(m_GameWindow, KeyboardCallback);
       //     glfwSetMouseButtonCallback(m_GameWindow, MouseCallback);
       //     glfwSetCursorPosCallback(m_GameWindow, CursorPositionCallback);

       //     if (glewInit() != GLEW_OK) {
       //         std::cout << "[ERROR] GLEW INITIALIZE FAILED" << std::endl;
       //         return false;
       //     }
       //     std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
       //     return true;
       // }
       // 
       // void WindowResize(GLFWwindow *p_GameWindow, int p_WindowWidth, int p_WindowHeight) {
       //     glViewport(0, 0, p_WindowWidth, p_WindowHeight);
       // }
       // 
       // void KeyboardCallback(GLFWwindow *p_GameWindow, int p_KeyboardInput, int p_ScanCode, int p_Action, int p_Mods) {
       //     Window *WindowPointer = (Window*)glfwGetWindowUserPointer(p_GameWindow);
       //     WindowPointer->m_Keyboard[p_KeyboardInput] = p_Action != GLFW_RELEASE;
       // }
       // 
       // void MouseCallback(GLFWwindow *p_GameWindow, int p_MouseInput, int p_Action, int p_Mods) {
       //      Window *WindowPointer = (Window*)glfwGetWindowUserPointer(p_GameWindow);
       //      WindowPointer->m_Mouse[p_MouseInput] = p_Action != GLFW_RELEASE;
       // }
       // 
       // void CursorPositionCallback(GLFWwindow *p_GameWindow, double p_XPosition, double p_YPosition) {
       //     Window *WindowPointer = (Window*)glfwGetWindowUserPointer(p_GameWindow);
       //     WindowPointer->m_XPosition = p_XPosition;
       //     WindowPointer->m_YPosition = p_YPosition;
       // }
    }
}
