#pragma once
#include "MathLibrary.hpp"

namespace JS_Engine {
    namespace MathLibrary {
        struct Matrix {
            //Union For Memory
            union {
                float Elements[4 * 4];
                Vector4 Column[4];
            };
            
            Matrix();
            Matrix(float p_Diagonal);
            //Get Column of Matrix
            Vector4 GetColumn(int p_Index) {
                p_Index * 4;
                return Vector4(Elements[p_Index], Elements[p_Index + 1], Elements[p_Index + 2], Elements[p_Index + 3]);
            }
            //Multiplication
            Vector2 Multiply(const Vector2 &p_Vector) const;
            Vector3 Multiply(const Vector3 &p_Vector) const;
            Vector4 Multiply(const Vector4 &p_Vector) const;
            Matrix &Multiply(const Matrix  &p_Matrix);
            //*= Operator Override
            Matrix &operator*=(const Matrix &p_Matrix);
            //* Operator Override
            friend Vector2 operator*(const Matrix &p_LValue, const Vector2 &p_RValue);
            friend Vector3 operator*(const Matrix &p_LValue, const Vector3 &p_RValue);
            friend Vector4 operator*(const Matrix &p_LValue, const Vector4 &p_RValue);
            friend Matrix  operator*(Matrix p_LValue, const Matrix &p_RValue);
            //Identity Matrix
            static Matrix Identiy();
            //Orthographic
            static Matrix Orthographic(float p_Left, float p_Right, float p_Bottom, float p_Top, float p_Near, float p_Far);
            //Perspective
            static Matrix Perspective(float p_FieldOfView, float p_AspectRatio, float p_Near, float p_Far);
            //Rotation
            static Matrix Rotate(float p_Angle, const Vector3 &p_Axis);
            //Translate
            static Matrix Translate(const Vector3 &p_Translation);
            //Scale
            static Matrix Scale(const Vector3 &p_Scale);
        };
    }
}