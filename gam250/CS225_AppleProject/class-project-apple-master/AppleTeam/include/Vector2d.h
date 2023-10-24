/************************************************************************
*	File name : Vector2d.h
*	Project name : apple
*   Author	    Primary author : Junseok Yang
*			    Secondary author : Seungguk Jang
*	File description : Making mathmatic vector2d.
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
struct [[nodiscard]] v2
{
    float x;
    float y;
};

struct [[nodiscard]] Vector2
{
public:
    int x, y;
    constexpr Vector2() noexcept
        :x(0), y(0)
    {
    }

    constexpr Vector2(int repeated_float) noexcept : x(repeated_float), y(repeated_float) {};

    constexpr Vector2(const int p_XValue, const int p_YValue) noexcept
        :x(p_XValue), y(p_YValue)
    {
    }
};