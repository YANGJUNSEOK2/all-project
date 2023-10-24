#pragma once

#include <SDL.h>
#include <glew.h>
#include "../SpriteGame/Sprite.hpp"
#include "../../Graphics/Shader/Shader.hpp"
#include "../../Error/Error.hpp"
#include "../GLSLProgram/GLSLProgram.hpp"
#include "../SpriteGame/GLTexture/GLTexture.hpp"
#include "../SpriteGame/ImageLoader/ImageLoader.hpp"

namespace JS_Engine {
    namespace MainSystem {

        enum class GameState
        {
            PLAY, EXIT
        };

        class MainGame
        {
        public:
            MainGame();
            ~MainGame();

            void GameRun();
        private:
            void InitSystem();
            void InitShaders();
            void GameLoop();
            void ProcessInput();
            void DrawGame();

            SDL_Window* m_Window;
            int m_ScreenWidth;
            int m_ScreenHeight;
            GameState m_GameState;

            Sprite m_Sprite;

            GLSLProgram m_ColorProgram;
            float m_time;

            GLTexture m_PlayerTexture;

            Graphics::Shader *m_ColorShader;
            Graphics::Shader& Color = *m_ColorShader;
        };
    }
}
