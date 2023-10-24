#pragma once
#include "../Render/Render.hpp"

namespace JS_Engine {
    namespace Graphics {
        class Sprite : public Render {
        public:
            Sprite(float p_XComponent, float p_YComponent, float p_Width, float p_Height, const MathLibrary::Vector4 &p_Color);
        };
    }
}