/************************************************************************
*	File name : Matrix4.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester
*************************************************************************/
#pragma once
#include "MathLibrary.hpp"

    template<typename T> struct Matrix4 {
        //Union For Memory

        union {
            T Elements[4][4];
            Vector4<T> Column[4];
        };

        Matrix4()
        {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++)
                {
                    Elements[i][j] = 0.0f;
                }
                Column[i] = { 0.0f };
            }
        }

        Matrix4(Vector4<T> Zero_column, Vector4<T> first_column, Vector4<T> second_column, Vector4<T> third_column)
        {
            Column[0] = Zero_column;
            Column[1] = (first_column);
            Column[2] = (second_column);
            Column[3] = (third_column);
        }

        Matrix4(T column0_row0, T column0_row1, T column0_row2, T column0_row3, T column1_row0, T column1_row1,
            T column1_row2, T column1_row3, T column2_row0, T column2_row1, T column2_row2, T column2_row3,
            T column3_row0, T column3_row1, T column3_row2, T column3_row3) noexcept
        {
            Column[0] = (column0_row0, column0_row1, column0_row2, column0_row3);
            Column[1] = (column1_row0, column1_row1, column1_row2, column1_row3);
            Column[2] = (column2_row0, column2_row1, column2_row2, column2_row3);
            Column[3] = (column3_row0, column3_row1, column3_row2, column3_row3);
        }

        Matrix4(T p_Diagonal)
        {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++)
                {
                    Elements[i][j] = 0.0f;
                }
            }
            Elements[0][0] = p_Diagonal;
            Elements[1][1] = p_Diagonal;
            Elements[2][2] = p_Diagonal;
            Elements[3][3] = p_Diagonal;
        }

        //Get Column of Matrix4
        Vector4<T> GetColumn(T p_Index) {
            p_Index *= 4;
            return Vector4<T>(Elements[p_Index], Elements[p_Index + 1], Elements[p_Index + 2], Elements[p_Index + 3]);
        }
        //Multiplication
        Vector2<T> Multiply(const Vector2<T>& p_Vector) const
        {
            T Xcomp = p_Vector.x;
            T Ycomp = p_Vector.y;
            return Vector2<T>(
                Column[0].x * Xcomp + Column[1].x * Ycomp + Column[2].x + Column[3].x,
                Column[0].y * Xcomp + Column[1].y * Ycomp + Column[2].y + Column[3].y
                );
        }
        Vector3<T> Multiply(const Vector3<T>& p_Vector) const
        {
            T Xcomp = p_Vector.x;
            T Ycomp = p_Vector.y;
            T Zcomp = p_Vector.z;
            return Vector3<T>(
                Column[0].x * Xcomp + Column[1].x * Ycomp + Column[2].x * Zcomp + Column[3].x,
                Column[0].y * Xcomp + Column[1].y * Ycomp + Column[2].y * Zcomp + Column[3].y,
                Column[0].z * Xcomp + Column[1].z * Ycomp + Column[2].z * Zcomp + Column[3].z
                );
        }
        Vector4<T> Multiply(const Vector4<T>& p_Vector) const
        {
            T Xcomp = p_Vector.x;
            T Ycomp = p_Vector.y;
            T Zcomp = p_Vector.z;
            T Wcomp = p_Vector.w;
            return Vector4<T>(
                Column[0].x * Xcomp + Column[1].x * Ycomp + Column[2].x * Zcomp + Column[3].x * Wcomp,
                Column[0].y * Xcomp + Column[1].y * Ycomp + Column[2].y * Zcomp + Column[3].y * Wcomp,
                Column[0].z * Xcomp + Column[1].z * Ycomp + Column[2].z * Zcomp + Column[3].z * Wcomp,
                Column[0].w * Xcomp + Column[1].w * Ycomp + Column[2].w * Zcomp + Column[3].w * Wcomp
                );
        }
        Matrix4<T>& Multiply(const Matrix4<T>& p_Matrix)
        {
            T MatrixData[4][4];
            for (int Row = 0; Row < 4; Row++) {
                for (int Column = 0; Column < 4; Column++) {
                    T Sum = 0.0f;
                    for (int Component = 0; Component < 4; Component++) {
                        Sum += Elements[Column][Component] * p_Matrix.Elements[Component][Row];
                    }
                    MatrixData[Column][Row] = Sum;
                }
            }
            memcpy(Elements, MatrixData, 4 * 4 * sizeof(float));
            return *this;
        }



        //*= Operator Override
        Matrix4<T>& operator*=(const Matrix4<T>& p_Matrix)
        {
            return Multiply(p_Matrix);
        }

        //Identity Matrix4
        static Matrix4<T> Identity()
        {
            return Matrix4(1.0f);
        }
        //Orthographic

        static Matrix4<T> Orthographic(T p_Left, T p_Right, T p_Bottom, T p_Top)
        {
            Matrix4 Result(1.0f);

            Result.Elements[0][0] = 2.0f / (p_Right - p_Left);
            Result.Elements[1][1] = 2.0f / (p_Top - p_Bottom);
            Result.Elements[2][2] = static_cast <T>(-1);

            Result.Elements[3][0] = (p_Left + p_Right) / (p_Left - p_Right);
            Result.Elements[3][1] = (p_Bottom + p_Top) / (p_Bottom - p_Top);

            return Result;
        }
        //Perspective

        static Matrix4<T> Perspective(T p_FieldOfView, T p_AspectRatio, T p_Near, T p_Far)
        {
            Matrix4 Result(1.0f);

            T ValueQ = 1.0f / tan(DegreeToRadian(0.5f * p_FieldOfView));
            T ValueA = ValueQ / p_AspectRatio;
            T ValueB = (p_Near + p_Far) / (p_Near - p_Far);
            T ValueC = (2.0f * p_Near * p_Far) / (p_Near - p_Far);

            Result.Elements[0][0] = ValueA;
            Result.Elements[1][1] = ValueQ;
            Result.Elements[2][2] = ValueB;
            Result.Elements[2][3] = -1.0f;
            Result.Elements[3][2] = ValueC;
            return Result;
        }
        //Rotation

        static Matrix4<T> Rotate(T p_Angle, const Vector3<T>& p_Axis)
        {
            Matrix4 Result(1.0f);

            T ValueX = p_Axis.x;
            T ValueY = p_Axis.y;
            T ValueZ = p_Axis.z;
            T ValueRadian = DegreeToRadian(p_Angle);
            T ValueSine = sin(ValueRadian);
            T ValueCosine = cos(ValueRadian);
            T OneMinusCosine = 1.0f - ValueCosine;

            Result.Elements[0][0] = ValueX * OneMinusCosine + ValueCosine;
            Result.Elements[0][1] = ValueX * ValueY * OneMinusCosine + ValueZ * ValueSine;
            Result.Elements[0][2] = ValueX * ValueZ * OneMinusCosine - ValueY * ValueSine;

            Result.Elements[1][0] = ValueX * ValueY * OneMinusCosine - ValueZ * ValueSine;
            Result.Elements[1][1] = ValueY * OneMinusCosine + ValueCosine;
            Result.Elements[1][2] = ValueY * ValueZ * OneMinusCosine + ValueX * ValueSine;

            Result.Elements[2][0] = ValueX * ValueZ * OneMinusCosine + ValueY * ValueSine;
            Result.Elements[2][1] = ValueY * ValueZ * OneMinusCosine - ValueX * ValueSine;
            Result.Elements[2][2] = ValueZ * OneMinusCosine + ValueCosine;
            return Result;
        }
        //Translate

        static Matrix4<T> Translate(const Vector3<T>& p_Translation)
        {
            Matrix4 Result(1.0f);

            Result.Elements[3][0] = p_Translation.x;
            Result.Elements[3][1] = p_Translation.y;
            Result.Elements[3][2] = p_Translation.z;
            return Result;
        }
        //Scale

        static Matrix4<T> Scale(const Vector3<T>& p_Scale)
        {
            Matrix4 Result(1.0f);

            Result.Elements[0][0] = p_Scale.x;
            Result.Elements[1][1] = p_Scale.y;
            Result.Elements[2][2] = p_Scale.z;
            return Result;
        }

    };

    //* Operator Override
    template<typename T>
    Vector2<T> operator*(const Matrix4<T>& p_LValue, const Vector2<T>& p_RValue)
    {
        return p_LValue.Multiply(p_RValue);
    }

    template<typename T>
    Vector3<T> operator*(const Matrix4<T>& p_LValue, const Vector3<T>& p_RValue)
    {
        return p_LValue.Multiply(p_RValue);
    }

    template<typename T>
    Vector4<T> operator*(const Matrix4<T>& p_LValue, const Vector4<T>& p_RValue)
    {
        return p_LValue.Multiply(p_RValue);
    }

    template<typename T>
    Matrix4<T>  operator*(Matrix4<T> p_LValue, const Matrix4<T>& p_RValue)
    {
        return p_LValue.Multiply(p_RValue);
    }