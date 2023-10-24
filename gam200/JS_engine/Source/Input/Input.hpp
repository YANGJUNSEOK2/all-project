
#pragma once
#include <glew.h>
#include <glfw3.h>
#include <bitset>
#include <../../Source/MathLibrary/MathLibrary.hpp>

namespace JS_Engine {
    namespace Input {
#define MaxKeyboard 1024
#define MaxMouse    32
        class Inputs
        {
        public:
            Inputs();
            ~Inputs()
            {
                instanceFlag = false;
            };
            //Use Input Functions
            static Inputs* getInstance();
            //Key & Mouse Reset
            void Reset();
            //Key set
            void SetKeyPressed(unsigned int key, unsigned int eType);
            //Key Pressed
            static bool IsKeyPressed(unsigned int key);
            //Key Triggered
            static bool IsKeyTriggered(unsigned int key);
            //Key Released
            static bool IsKeyReleased(unsigned int key);
            //Any Key Pressed
            static bool IsAnyKeyPressed();
            //Any Key Triggered
            static bool IsAnyKeyTriggered();
            //Any Key Released
            static bool IsAnyKeyReleased();
            //Set Mouse position
            void SetMousePos(float x, float y);
            //Get Mouse Position
            MathLibrary::Vector2 GetMousePos();
            //Mouse Set
            void SetMousePressed(int mButton, unsigned int eMouseButton);
            //Mouse Pressed
            static bool IsMousePressed(int key);
            //Mouse Triggered
            static bool IsMouseTriggered(int key);
            //Mouse DoubleClicked
            static bool IsMouseDoubleClicked(int key);
            //Mouse Released
            static bool IsMouseReleased(int key);

        private:
            static Inputs* instance;
            static bool instanceFlag;
        };
    }
}