/************************************************************************
*	File name : Vector4.hpp
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

    template <typename T>struct Vector4 {
    public:
        //Components
        T x, y, z, w;
        Vector4() noexcept
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
            w = 0.0f;
        }

        Vector4(T repeated_float) noexcept : x(repeated_float), y(repeated_float), z(repeated_float), w(repeated_float) {};



        Vector4(const T p_XValue, const T p_YValue, const T p_ZValue, const T p_WValue) noexcept
        {
            this->x = p_XValue;
            this->y = p_YValue;
            this->z = p_ZValue;
            this->w = p_WValue;
        }
        T GetXComp(void)noexcept
        {
            return x;
        }
        T GetYComp(void)noexcept
        {
            return y;
        }
        T GetZComp(void)noexcept
        {
            return z;
        }
        T GetWComp(void)noexcept
        {
            return w;
        }
        //Addition
        Vector4<T>& Add(const Vector4<T>& p_Vector) noexcept
        {
            x += p_Vector.x;
            y += p_Vector.y;
            z += p_Vector.z;
            w += p_Vector.w;
            return *this;
        }
        //Subtraction
        Vector4<T>& Subtract(const Vector4<T>& p_Vector)noexcept
        {
            x -= p_Vector.x;
            y -= p_Vector.y;
            z -= p_Vector.z;
            w -= p_Vector.w;
            return *this;
        }
        //Multiplication
        Vector4<T>& Multiply(const Vector4<T>& p_Vector)noexcept {
            x *= p_Vector.x;
            y *= p_Vector.y;
            z *= p_Vector.z;
            w *= p_Vector.w;
            return *this;
        }
        //Division
        Vector4<T>& Divide(const Vector4<T>& p_Vector)noexcept {
            x /= p_Vector.x;
            y /= p_Vector.y;
            z /= p_Vector.z;
            w /= p_Vector.w;
            return *this;
        }
        //+= Operator Override
        Vector4<T>& operator+=(const Vector4<T>& p_Vector)noexcept {
            return Add(p_Vector);
        }
        //-= Operator Override
        Vector4<T>& operator-=(const Vector4<T>& p_Vector)noexcept {
            return Subtract(p_Vector);
        }
        //*= Operator Override
        Vector4<T>& operator*=(const Vector4<T>& p_Vector)noexcept {
            return Multiply(p_Vector);
        }
        // /= Operator Override
        Vector4<T>& operator/=(const Vector4<T>& p_Vector)noexcept {
            return Divide(p_Vector);
        }
        //== Operator Override
        bool operator==(const Vector4<T>& p_Vector)noexcept {
            return (x == p_Vector.x
                && y == p_Vector.y
                && z == p_Vector.z
                && w == p_Vector.w);
        }
        //!= Operator Override
        bool operator!=(const Vector4<T>& p_Vector)noexcept {
            return !(*this == p_Vector);
        }

    };

    //+ Operator Override
    template <typename T>
    Vector4<T> operator+(Vector4<T> p_LValue, const Vector4<T>& p_RValue)noexcept {
        return p_LValue.Add(p_RValue);
    }
    //- Operator Override
    template <typename T>
    Vector4<T> operator-(Vector4<T> p_LValue, const Vector4<T>& p_RValue)noexcept {
        return p_LValue.Subtract(p_RValue);
    }
    //* Operator Override
    template <typename T>
    Vector4<T> operator*(Vector4<T> p_LValue, const Vector4<T>& p_RValue)noexcept {
        return p_LValue.Multiply(p_RValue);
    }
    // / Operator Override
    template <typename T>
    Vector4<T> operator/(Vector4<T> p_LValue, const Vector4<T>& p_RValue)noexcept {
        return p_LValue.Divide(p_RValue);
    }
    //* Operator Override
    template <typename T>
    Vector4<T> operator*(const Vector4<T>& p_Vector, T scale) noexcept
    {
        Vector4<T> multiply;
        multiply.x = p_Vector.x * scale;
        multiply.y = p_Vector.y * scale;
        multiply.z = p_Vector.z * scale;
        multiply.w = p_Vector.w * scale;
        return multiply;
    }
    //* Operator Override
    template <typename T>
    Vector4<T> operator*(T scale, const Vector4<T>& p_Vector) noexcept
    {
        Vector4<T> multiply;
        multiply.x = p_Vector.x * scale;
        multiply.y = p_Vector.y * scale;
        multiply.z = p_Vector.z * scale;
        multiply.w = p_Vector.w * scale;
        return multiply;
    }

    //<< Operator Override
    template <typename T>
    std::ostream& operator<<(std::ostream& p_Stream, const Vector4<T>& p_Vector)noexcept {
        p_Stream << "[Vector4] (" << p_Vector.x << ", " << p_Vector.y << ", " << p_Vector.z << ", " << p_Vector.w << ")";
        return p_Stream;
    }

