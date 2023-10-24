#pragma once
#include "../MathLibrary/MathLibrary.hpp"
#include "../Graphics/Shader/Shader.hpp"

namespace JS_Engine {
    namespace MoveSystem {
        class Move:Graphics::Shader
        {
        public:
            Move();
            ~Move();

            void Init();
            MathLibrary::Vector2 GetMoving() const;
            void SetMoving(const MathLibrary::Vector2 p_Moving);
        private:
            MathLibrary::Vector2 m_Moving{};
        };
    }
}
