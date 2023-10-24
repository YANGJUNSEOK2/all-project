
#include "Input.hpp"

namespace JS_Engine {
    namespace Input {
        //Key Memory
        std::bitset<MaxKeyboard> m_KeyPressed;
        std::bitset<MaxKeyboard> m_KeyTriggered;
        std::bitset<MaxKeyboard> m_KeyReleased;
        //Mouse Memory
        MathLibrary::Vector2 m_MousePos;
        std::bitset<MaxMouse> m_MousePressed;
        std::bitset<MaxMouse> m_MouseTriggered;
        std::bitset<MaxMouse> m_MouseDoubleclick;
        std::bitset<MaxMouse> m_MouseReleased;

        bool Inputs::instanceFlag = false;
        Inputs* Inputs::instance = NULL;
        //getInstance:: Use Input Functions
        Inputs* Inputs::getInstance()
        {
            if (!instance) {
                instanceFlag = true;
            }
            return instance;
        }

        void Inputs::Reset()
        {
            m_KeyReleased.reset();
            m_KeyTriggered.reset();
            m_MouseReleased.reset();
            m_MouseTriggered.reset();
        }

        void Inputs::SetKeyPressed(unsigned key, unsigned eType)
        {
            if (eType == GLFW_PRESS)
            {
                m_KeyPressed.set(key);
                m_KeyTriggered.set(key);
            }
            else if (eType == GLFW_RELEASE)
            {
                m_KeyReleased.set(key);
                m_KeyPressed.reset(key);
            }
        }

        bool Inputs::IsKeyPressed(unsigned key)
        {
            if (key >= MaxKeyboard) {
                return false;
            }
            return m_KeyPressed[key];
        }

        bool Inputs::IsKeyTriggered(unsigned key)
        {
            if (key >= MaxKeyboard) {
                return false;
            }
            return m_KeyTriggered[key];
        }

        bool Inputs::IsKeyReleased(unsigned key)
        {
            if (key >= MaxKeyboard) {
                return false;
            }
            return m_KeyReleased[key];
        }

        bool Inputs::IsAnyKeyPressed()
        {
            return m_KeyPressed.any();
        }

        bool Inputs::IsAnyKeyTriggered()
        {
            return m_KeyTriggered.any();
        }

        bool Inputs::IsAnyKeyReleased()
        {
            return m_KeyReleased.any();
        }

        void Inputs::SetMousePos(float x, float y)
        {
            (x, y);
        }

        MathLibrary::Vector2 Inputs::GetMousePos()
        {
            return MathLibrary::Vector2(0, 0);
        }

        void Inputs::SetMousePressed(int mButton, unsigned eMouseButton)
        {
            if (eMouseButton == GLFW_PRESS)
            {
                m_MousePressed.set(mButton);
                m_MouseTriggered.set(mButton);
            }
            else if (eMouseButton == GLFW_RELEASE)
            {
                m_MouseReleased.set(mButton);
                m_MousePressed.reset(mButton);
            }
        }

        bool Inputs::IsMousePressed(int key)
        {
            return m_MousePressed[key];
        }

        bool Inputs::IsMouseTriggered(int key)
        {
            return m_MouseTriggered[key];
        }

        //bool Inputs::IsMouseDoubleClicked(int key)
        //{
        //    return m_MouseDoubleclick[key];
        //}

        bool Inputs::IsMouseReleased(int key)
        {
            return m_MouseReleased[key];
        }
    }
}