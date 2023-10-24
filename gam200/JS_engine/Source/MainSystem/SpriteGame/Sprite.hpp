#pragma once
#include <glew.h>

namespace JS_Engine {
    namespace MainSystem {
        class Sprite
        {
        public:
            Sprite();
            ~Sprite();

            void Init(float p_X, float p_Y, float p_Width, float p_Height);


            void Draw();

        private:
            float m_X;
            float m_Y;
            float m_Width;
            float m_Height;
            GLuint m_VBOId;
        };


    }
}
