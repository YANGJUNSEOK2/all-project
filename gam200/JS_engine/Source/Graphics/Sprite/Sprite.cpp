#include "Sprite.hpp"

namespace JS_Engine {
    namespace Graphics {
        using namespace MathLibrary;

        Sprite::Sprite(float p_XComponent, float p_YComponent, float p_Width, float p_Height, const Vector4 &p_Color)
            : Render(Vector3(p_XComponent, p_YComponent, 0), Vector2(p_Width, p_Height), p_Color) { }
    }
}