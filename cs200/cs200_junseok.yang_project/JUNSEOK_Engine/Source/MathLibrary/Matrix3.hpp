/************************************************************************
*	File name : Matrix3.hpp
*	Project name : Pinata
* Author	        Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include "MathLibrary.hpp"

template<typename T> struct Matrix3 {
    //Union For Memory
    union {
        T Elements[3][3];
        Vector3<T> Column[3];
    };

    constexpr Matrix3() noexcept
    {
        Elements[0][0] = 0;
        Elements[0][1] = 0;
        Elements[0][2] = 0;
        Elements[1][0] = 0;
        Elements[1][1] = 0;
        Elements[1][2] = 0;
        Elements[2][0] = 0;
        Elements[2][1] = 0;
        Elements[2][2] = 0;
    }

    constexpr Matrix3(Vector3<T> Zero_column, Vector3<T> first_column, Vector3<T> second_column) noexcept
    {
        Elements[0][0] = Zero_column.x;
        Elements[0][1] = Zero_column.y;
        Elements[0][2] = Zero_column.z;
        Elements[1][0] = first_column.x;
        Elements[1][1] = first_column.y;
        Elements[1][2] = first_column.z;
        Elements[2][0] = second_column.x;
        Elements[2][1] = second_column.y;
        Elements[2][2] = second_column.z;
    }

    constexpr Matrix3(T column0_row0, T column0_row1, T column0_row2, T column1_row0, T column1_row1,
        T column1_row2, T column2_row0, T column2_row1, T column2_row2) noexcept
    {
        Elements[0][0] = column0_row0;
        Elements[0][1] = column0_row1;
        Elements[0][2] = column0_row2;
        Elements[1][0] = column1_row0;
        Elements[1][1] = column1_row1;
        Elements[1][2] = column1_row2;
        Elements[2][0] = column2_row0;
        Elements[2][1] = column2_row1;
        Elements[2][2] = column2_row2;
    }

    constexpr Matrix3(T p_Diagonal) noexcept
    {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
            {
                Elements[i][j] = 0.0f;
            }
        }
        Elements[0][0] = p_Diagonal;
        Elements[1][1] = p_Diagonal;
        Elements[2][2] = p_Diagonal;
    }

    //Get Column of Matrix3
    constexpr Vector3<T> GetColumn(T p_Index) noexcept {
        p_Index *= 3;
        return Vector3<T>(Elements[p_Index], Elements[p_Index + 1], Elements[p_Index + 2]);
    }

    //() Operator Override
    template<typename T>
    constexpr T operator()(T column, T row) const noexcept
    {
        assert((column >= 0) && (column < 3));
        assert((row >= 0) && (row < 3));
        return Elements[column][row];
    }
    //() Operator Override
    template<typename T>
    constexpr T& operator()(T column, T row) noexcept
    {
        assert((column >= 0) && (column < 3));
        assert((row >= 0) && (row < 3));
        return Elements[column][row];
    }
};

template<typename T>
constexpr Matrix3<T> operator*(const Matrix3<T>& m1, const Matrix3<T>& m2) noexcept
{
    Matrix3<T> multiple;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            multiple.Elements[j][i] = m1.Elements[0][i] * m2.Elements[j][0]
            + m1.Elements[1][i] * m2.Elements[j][1]
            + m1.Elements[2][i] * m2.Elements[j][2];
        }
    }
    return multiple;
}
//* Operator Override
template<typename T>
constexpr Vector3<T> operator*(const Matrix3<T>& m, Vector3<T> v) noexcept
{
    Vector3<T> multiply;
    multiply.x = m(0, 0)*v.x + m(1, 0)*v.y + m(2, 0)*v.z;
    multiply.y = m(0, 1)*v.x + m(1, 1)*v.y + m(2, 1)*v.z;
    multiply.z = m(0, 2)*v.x + m(1, 2)*v.y + m(2, 2)*v.z;
    return multiply;
}

template<typename T>
constexpr Matrix3<T> build_rotation(T angle_in_radians) noexcept
{
    Matrix3<T> rotation(1.0f);
    T zero = 0;

    rotation.Elements[0][0] = cos(angle_in_radians);
    rotation.Elements[1][0] = -sin(angle_in_radians);
    rotation.Elements[2][0] = 0;

    rotation.Elements[0][1] = sin(angle_in_radians);
    rotation.Elements[1][1] = cos(angle_in_radians);
    rotation.Elements[2][1] = 0;

    rotation.Elements[0][2] = 0;
    rotation.Elements[1][2] = 0;
    rotation.Elements[2][2] = 1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (abs(rotation.Elements[i][j]) <= std::numeric_limits<T>::epsilon())
            {
                rotation.Elements[i][j] = (T)zero;
            }
        }
    }
    return rotation;
}

template<typename T>
constexpr Matrix3<T> build_identity() noexcept
{
    return Matrix3<T>
        (1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

template<typename T>
constexpr Matrix3<T> build_scale(T scale_x, T scale_y) noexcept
{
    return Matrix3<T>(scale_x, 0, 0, 0, scale_y, 0, 0, 0, 1);
}

template<typename T>
constexpr Matrix3<T> build_scale(T scale) noexcept
{
    return Matrix3<T>(scale, 0, 0, 0, scale, 0, 0, 0, 1);
}

template<typename T>
constexpr Matrix3<T> build_scale(const Vector2<T>& scale) noexcept
{
    return Matrix3<T>(scale.x, 0, 0, 0, scale.y, 0, 0, 0, 1);
}

template<typename T>
constexpr Matrix3<T> build_translation(T translate_x, T translate_y) noexcept
{
    return Matrix3<T>(1, 0, 0, 0, 1, 0, translate_x, translate_y, 1);
}

template<typename T>
constexpr Matrix3<T> build_translation(const Vector2<T>& translation) noexcept
{
    return Matrix3<T>(1, 0, 0, 0, 1, 0, translation.x, translation.y, 1);
}
