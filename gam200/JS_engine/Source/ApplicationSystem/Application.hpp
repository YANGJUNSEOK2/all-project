
#pragma once
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <../../Source/WindowSystem/WindowSystem.hpp>

namespace JS_Engine {
    namespace ApplicationSystem {
        class Application
        {
        public:
            Application();
            ~Application();
            //Application Initialize
            void Initialize();
            //Application Update
            void Update();

        private:
        };
    }
}