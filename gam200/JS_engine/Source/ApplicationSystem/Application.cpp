
#include "Application.hpp"

namespace JS_Engine {
    namespace ApplicationSystem {

            Application::Application()
            {
                std::cout << "Constructor Application" << std::endl;
            }

            Application::~Application()
            {
                std::cout << "Destructor Application" << std::endl;
            }

            void Application::Initialize()
            {
                std::cout << "Initialize Application" << std::endl;
            }

            void Application::Update()
            {
                
            }
    }
}