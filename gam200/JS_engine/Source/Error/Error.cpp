
#include"Error.hpp"
#include <cstdlib>
#include <iostream>
#include <SDL.h>

namespace JS_Engine {
    namespace ErrorSystem {
        void FatalError(std::string p_errorString)
        {
            std::cout << p_errorString << std::endl;
            std::cout << "Enter any KEY to quit... ";
            int temp;
            std::cin >> temp;
            SDL_Quit();
            exit(69);
        }
    }
}