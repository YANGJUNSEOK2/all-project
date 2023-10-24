/*
junseok.yang
assignment1
cs230
spring 2019
*/
#include <CS230/math/vector2.hpp>
#include <cassert>
#include <limits>

#include <cmath>

namespace CS230
{
    vector2::vector2() noexcept : x(0), y(0) {};
    vector2::vector2(float repeated_float) noexcept : x(repeated_float), y(repeated_float) {};
    vector2::vector2(float fx, float fy) noexcept : x(fx), y(fy) {};

    void operator+=(vector2& v, const vector2& adding_vector) noexcept
    {
        v.x += adding_vector.x;
        v.y += adding_vector.y;
    }

    void operator-=(vector2& v, const vector2& subtracting_vector) noexcept
    {
        v.x -= subtracting_vector.x;
        v.y -= subtracting_vector.y;
    }

    void operator*=(vector2& v, float scale) noexcept
    {
        v.x *= scale;
        v.y *= scale;
    }

    void operator/=(vector2& v, float divisor) noexcept
    {
        assert(divisor != 0.0f);
        {
            v.x /= divisor;
            v.y /= divisor;
        }
    }

    vector2 operator-(const vector2& v) noexcept
    {
        vector2 negative;
        negative.x = -v.x;
        negative.y = -v.y;
        return negative;
    }

    vector2 operator+(const vector2& v1, const vector2& v2) noexcept
    {
        vector2 add;
        add.x = v1.x + v2.x;
        add.y = v1.y + v2.y;
        return add;
    }

    vector2 operator-(const vector2& v1, const vector2& v2) noexcept
    {
        vector2 sub;
        sub.x = v1.x - v2.x;
        sub.y = v1.y - v2.y;
        return sub;
    }

    vector2 operator*(const vector2& v, float scale) noexcept
    {
        vector2 multiply;
        multiply.x = v.x * scale;
        multiply.y = v.y * scale;
        return multiply;
    }

    vector2 operator*(float scale, const vector2& v) noexcept
    {
        vector2 multiply;
        multiply.x = scale * v.x;
        multiply.y = scale * v.y;
        return multiply;
    }

    vector2 operator/(const vector2& v, float divisor) noexcept
    {
        assert(divisor != 0.0f);
        {
            vector2 divide;
            divide.x = v.x / divisor;
            divide.y = v.y / divisor;
            return divide;
        }

    }

    bool operator==(const vector2& v1, const vector2& v2) noexcept
    {
        if (std::abs(v1.x - v2.x) <= std::numeric_limits<float>::epsilon()
            && std::abs(v1.y - v2.y) <= std::numeric_limits<float>::epsilon())
        {
            return true;
        }
        else
            return false;
    }

    bool operator!=(const vector2& v1, const vector2& v2) noexcept
    {
        if (operator==(v1, v2))
        {
            return false;
        }
        else
            return true;
    }

    float dot(vector2 a, vector2 b) noexcept
    {
        return float((a.x * b.x) + (a.y * b.y));
    }

    vector2 perpendicular_to(vector2 a) noexcept
    {
        return vector2(-a.y, a.x);
    }

    float magnitude_squared(vector2 a) noexcept
    {
        return (dot(a,a));
    }

    float magnitude(vector2 a) noexcept
    {
        return float(std::sqrt(magnitude_squared(a)));
    }

    vector2 normalize(vector2 a) noexcept
    {
        assert(a.x / magnitude(a) != 0);
        assert(a.y / magnitude(a) != 0);
        vector2 normal;
        normal = a / magnitude(a);
        return normal;
    }

    float distance_between_squared(vector2 a, vector2 b) noexcept
    {
        return magnitude_squared(a - b);
    }

    float distance_between(vector2 a, vector2 b) noexcept
    {
        return float(std::sqrt(distance_between_squared(a, b)));
    }

    float angle_between(vector2 a, vector2 b) noexcept
    {
        assert(dot(a, b) / (magnitude(a)*magnitude(b)) != 0);
        return float(std::acos(dot(a, b) / (magnitude(a)*magnitude(b))));
    }

    vector2 rotate_by(float angle_in_radians, vector2 v) noexcept
    {
        assert(angle_in_radians != 0);
        {
            return vector2(std::cos(angle_in_radians) * v.x - std::sin(angle_in_radians) * v.y
                , std::sin(angle_in_radians) * v.x + std::cos(angle_in_radians) * v.y);
        }
    }
}
