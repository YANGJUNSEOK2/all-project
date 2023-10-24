/************************************************************************
*	File name : Vector3.hpp
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

template<typename T> struct  Vector3 {
public:
    //Components
    T x, y, z;

    Vector3() noexcept
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }
    Vector3(T repeated_float) noexcept : x(repeated_float), y(repeated_float), z(repeated_float) {};



    Vector3(const T p_XValue, const T p_YValue, const T p_ZValue) noexcept
    {
        this->x = p_XValue;
        this->y = p_YValue;
        this->z = p_ZValue;
    }
    //Get Component Value
    T GetXComp(void) noexcept
    {
        return x;
    }
    //Get Component Value
    T GetYComp(void) noexcept
    {
        return y;
    }
    //Get Component Value
    T GetZComp(void) noexcept
    {
        return z;
    }
    //Addition
    Vector3<T>& Add(const Vector3<T>& p_Vector) noexcept
    {
        x += p_Vector.x;
        y += p_Vector.y;
        z += p_Vector.z;
        return *this;
    }
    //Subtraction
    Vector3<T>& Subtract(const Vector3<T>& p_Vector) noexcept
    {
        x -= p_Vector.x;
        y -= p_Vector.y;
        z -= p_Vector.z;
        return *this;
    }
    //Multiplication
    Vector3<T>& Multiply(const Vector3<T>& p_Vector) noexcept
    {
        x *= p_Vector.x;
        y *= p_Vector.y;
        z *= p_Vector.z;
        return *this;
    }
    //Division
    Vector3<T>& Divide(const Vector3<T>& p_Vector) noexcept
    {
        x /= p_Vector.x;
        y /= p_Vector.y;
        z /= p_Vector.z;
        return *this;
    }
    //+= Operator Override
    Vector3<T>& operator+=(const Vector3<T>& p_Vector) noexcept
    {
        return Add(p_Vector);
    }
    //-= Operator Override
    Vector3<T>& operator-=(const Vector3<T>& p_Vector) noexcept
    {
        return Subtract(p_Vector);
    }
    //*= Operator Override
    Vector3<T>& operator*=(const Vector3<T>& p_Vector) noexcept
    {
        return Multiply(p_Vector);
    }
    // /= Operator Override
    Vector3<T>& operator/=(const Vector3<T>& p_Vector) noexcept
    {
        return Divide(p_Vector);
    }
    //== Operator Override
    bool operator==(const Vector3<T>& p_Vector) noexcept
    {
        return (x == p_Vector.x && y == p_Vector.y && z == p_Vector.z);
    }
    //!= Operator Override
    bool operator!=(const Vector3<T>& p_Vector) noexcept
    {
        return !(*this == p_Vector);
    }
};
//+ Operator Override
template<typename T>
Vector3<T> operator+(Vector3<T> p_LValue, const Vector3<T>& p_RValue) noexcept
{
    return p_LValue.Add(p_RValue);
}
//- Operator Override
template<typename T>
Vector3<T> operator-(Vector3<T> p_LValue, const Vector3<T>& p_RValue) noexcept
{
    return p_LValue.Subtract(p_RValue);
}
//* Operator Override
template<typename T>
Vector3<T> operator*(Vector3<T> p_LValue, const Vector3<T>& p_RValue) noexcept
{
    return p_LValue.Multiply(p_RValue);
}
// / Operator Override
template<typename T>
Vector3<T> operator/(Vector3<T> p_LValue, const Vector3<T>& p_RValue) noexcept
{
    return p_LValue.Divide(p_RValue);
}

//<< Operator Override
template<typename T>
std::ostream& operator<<(std::ostream& p_Stream, const Vector3<T>& p_Vector) noexcept
{
    p_Stream << "[Vector3] (" << p_Vector.x << ", " << p_Vector.y << ", " << p_Vector.z << ")";
    return p_Stream;
}
//dot product
template<typename T>
T dot(Vector3<T> p_LValue, Vector3<T> p_RValue) noexcept
{
    return T((p_LValue.x * p_RValue.x) + (p_LValue.y * p_RValue.y) + (p_LValue.z * p_RValue.z));
}
//cross product
template<typename T>
Vector3<T> cross(Vector3<T> p_LValue, Vector3<T> p_RValue) noexcept
{
    return Vector3<T>((p_LValue.y * p_RValue.z - p_LValue.z * p_RValue.y), (p_LValue.z * p_RValue.x - p_LValue.x * p_RValue.z), (p_LValue.x * p_RValue.y - p_LValue.y * p_RValue.x));
}
//magnitude to Squared
template<typename T>
T magnitude_Squared(Vector3<T> p_Vector) noexcept
{
    return T(dot(p_Vector, p_Vector));
}
//magnitude
template<typename T>
T magnitude(Vector3<T> p_Vector) noexcept
{
    return T(std::sqrt(magnitude_squared(p_Vector)));
}
//vector normalize
template<typename T>
Vector3<T> normalize(Vector3<T> p_Vector) noexcept
{
    assert(p_Vector.x / magnitude(p_Vector) != 0);
    assert(p_Vector.y / magnitude(p_Vector) != 0);
    assert(p_Vector.z / magnitude(p_Vector) != 0);
    Vector3<T> normal;
    normal = p_Vector / magnitude(p_Vector);
    return normal;
}
//distance Between Squared
template<typename T>
T distance_Between_Squared(Vector3<T> p_LValue, Vector3<T> p_RValue) noexcept
{
    return T(magnitude_Squared(p_LValue - p_RValue));
}
//vector distance
template<typename T>
T distance_Between(Vector3<T> p_LValue, Vector3<T> p_RValue) noexcept
{
    return T(std::sqrt(distance_Between_Squared(p_LValue, p_RValue)));
}
//vector angle
template<typename T>
T angle_Between(Vector3<T> p_LValue, Vector3<T> p_RValue) noexcept
{
    assert(dot(p_LValue, p_RValue) / (magnitude(p_LValue) * magnitude(p_RValue)) != 0);
    return float(std::acos(dot(p_LValue, p_RValue) / (magnitude(p_LValue) * magnitude(p_RValue))));
}