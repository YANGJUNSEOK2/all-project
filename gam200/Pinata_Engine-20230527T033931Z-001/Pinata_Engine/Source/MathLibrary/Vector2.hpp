/************************************************************************
*	File name : Vector2.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester
*************************************************************************/
#pragma once
#include <iostream>
#include <cassert>

template <typename T>struct  Vector2 {
public:
    //Components
    T x, y;
    Vector2() noexcept
    {
        x = 0.0f;
        y = 0.0f;
    }

    Vector2(T repeated_float) noexcept : x(repeated_float), y(repeated_float) {};

    //Vector2(T fx, T fy) noexcept : x(fx), y(fy){};

    Vector2(const T p_XValue, const T p_YValue) noexcept
    {
        this->x = p_XValue;
        this->y = p_YValue;
    }
    //Get Component Value
    T GetXComponent(void) noexcept
    {
        return x;
    }
    //Get Component Value
    T GetYComponent(void) noexcept
    {
        return y;
    }
    //Addition
    template <typename T>
    Vector2<T>& Add(const Vector2<T>& p_Vector) noexcept
    {
        x += p_Vector.x;
        y += p_Vector.y;
        return *this;
    }
    //Subtraction
    template <typename T>
    Vector2<T>& Subtract(const Vector2<T>& p_Vector) noexcept
    {
        x -= p_Vector.x;
        y -= p_Vector.y;
        return *this;
    }
    //Multiplication
    template <typename T>
    Vector2<T>& Multiply(const Vector2<T>& p_Vector) noexcept
    {
        x *= p_Vector.x;
        y *= p_Vector.y;
        return *this;
    }
    //Division
    template <typename T>
    Vector2<T>& Divide(const Vector2<T>& p_Vector) noexcept
    {
        x /= p_Vector.x;
        y /= p_Vector.y;
        return *this;
    }


    //+= Operator Override
    template <typename T>
    Vector2<T>& operator+=(const Vector2<T>& p_Vector) noexcept
    {
        return Add(p_Vector);
    }
    //-= Operator Override
    template <typename T>
    Vector2<T>& operator-=(const Vector2<T>& p_Vector) noexcept
    {
        return Subtract(p_Vector);
    }
    //*= Operator Override
    template <typename T>
    Vector2<T>& operator*=(const Vector2<T>& p_Vector) noexcept
    {
        return Multiply(p_Vector);
    }
    // /= Operator Override
    template <typename T>
    Vector2<T>& operator/=(const Vector2<T>& p_Vector) noexcept
    {
        return Divide(p_Vector);
    }
    //== Operator Override
    template <typename T>
    bool operator==(const Vector2<T>& p_Vector) noexcept
    {
        return (x == p_Vector.x && y == p_Vector.y);
    }
    //!= Operator Override
    template <typename T>
    bool operator!=(const Vector2<T>& p_Vector) noexcept
    {
        return !(*this == p_Vector);
    }
};
//- Operator Override
template <typename T>
Vector2<T> operator-(const Vector2<T>& p_Vector) noexcept
{
    Vector2<T> return_vector;
    return_vector.x = -p_Vector.x;
    return_vector.y = -p_Vector.y;
    return return_vector;
}
//+Operator Override
template <typename T>
Vector2<T> operator+(Vector2<T> p_LValue, const Vector2<T>& p_RValue) noexcept
{
    return p_LValue.Add(p_RValue);
}
//- Operator Override
template <typename T>
Vector2<T> operator-(Vector2<T> p_LValue, const Vector2<T>& p_RValue) noexcept
{
    return p_LValue.Subtract(p_RValue);
}
//* Operator Override
template <typename T>
Vector2<T> operator*(Vector2<T> p_LValue, const Vector2<T>& p_RValue) noexcept
{
    return p_LValue.Multiply(p_RValue);
}
// / Operator Override
template <typename T>
Vector2<T> operator/(Vector2<T> p_LValue, const Vector2<T>& p_RValue) noexcept
{
    return p_LValue.Divide(p_RValue);
}
//* Operator Override
template <typename T>
Vector2<T> operator*(const Vector2<T>& p_Vector, T scale) noexcept
{
    Vector2<T> multiply;
    multiply.x = p_Vector.x * scale;
    multiply.y = p_Vector.y * scale;
    return multiply;
}
//* Operator Override
template <typename T>
Vector2<T> operator*(T scale, const Vector2<T>& p_Vector) noexcept
{
    Vector2<T> multiply;
    multiply.x = scale * p_Vector.x;
    multiply.y = scale * p_Vector.y;
    return multiply;
}
// / Operator Override
template <typename T>
Vector2<T> operator/(const Vector2<T>& p_Vector, T divisor) noexcept
{
    assert(divisor != 0.0f);

    Vector2<T> divide;
    divide.x = p_Vector.x / divisor;
    divide.y = p_Vector.y / divisor;
    return divide;

}
//<< Operator Override
template <typename T>
std::ostream& operator<<(std::ostream& p_Stream, const Vector2<T>& p_Vector) noexcept
{
    p_Stream << "[Vector2] (" << p_Vector.x << ", " << p_Vector.y << ")";
    return p_Stream;
}
//dot product
template <typename T>
T dot(Vector2<T> p_LValue, Vector2<T> p_RValue) noexcept
{
    return T((p_LValue.x * p_RValue.x) + (p_LValue.y * p_RValue.y));
}
//perpendicular
template <typename T>
Vector2<T> perpendicular(Vector2<T> p_Vector) noexcept
{
    return Vector2<T>(-p_Vector.y, p_Vector.x);
}
//magnitude to Squared
template <typename T>
T magnitude_Squared(Vector2<T> p_Vector) noexcept
{
    return dot(p_Vector, p_Vector);
}
//magnitude
template <typename T>
T magnitude(Vector2<T> p_Vector) noexcept
{
    return T(std::sqrt(magnitude_Squared(p_Vector)));
}
//vector normalize
template <typename T>
Vector2<T> normalize(Vector2<T> p_Vector) noexcept
{
    assert(magnitude(p_Vector) != 0);
    Vector2<T> normal;
    normal = p_Vector / magnitude(p_Vector);
    return normal;
}
//distance Between Squared
template <typename T>
T distance_Between_Squared(Vector2<T> p_LValue, Vector2<T> p_RValue) noexcept
{
    return magnitude_Squared(p_LValue - p_RValue);
}
//vector distance
template <typename T>
T distance_Between(Vector2<T> p_LValue, Vector2<T> p_RValue) noexcept
{
    return T(std::sqrt(distance_Between_Squared(p_LValue, p_RValue)));
}
//vector angle
template <typename T>
T angle_Between(Vector2<T> p_LValue, Vector2<T> p_RValue) noexcept
{
    assert(dot(p_LValue, p_RValue) / (magnitude(p_LValue) * magnitude(p_RValue)) != 0);
    return T(std::acos(dot(p_LValue, p_RValue) / (magnitude(p_LValue) * magnitude(p_RValue))));
}
//vector rotate
template <typename T>
Vector2<T> rotate_By(T angle_in_radians, Vector2<T> p_Vector) noexcept
{
    //assert(angle_in_radians != 0);
    {
        return Vector2<T>(std::cos(angle_in_radians) * p_Vector.x - std::sin(angle_in_radians) * p_Vector.y
            , std::sin(angle_in_radians) * p_Vector.x + std::cos(angle_in_radians) * p_Vector.y);
    }
}