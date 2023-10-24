/*
 * Rudy Castan
 * Graphics Library
 * CS230
 */
#pragma once
namespace CS230
{
    class [[nodiscard]] Color4f
    {
    public:
        float red   = 0;
        float green = 0;
        float blue  = 0;
        float alpha = 1.0f;

    public:
   
    };

    static_assert(sizeof(Color4f) == 16, "Color4f should be 4 floats");

    class Color4ub;
    Color4f to_color4f(const Color4ub& eight_bit_color);
}
