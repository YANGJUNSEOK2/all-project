#pragma once
#include <iostream>

namespace JS_Engine {
    namespace MathLibrary {
        struct Vector2 {
            //Components
            float XComponent;
            float YComponent;

            Vector2();
            Vector2(const float &p_XValue, const float &p_YValue);
            //Addition
            Vector2 &Add(const Vector2 &p_Vector);
            //Subtraction
            Vector2 &Subtract(const Vector2 &p_Vector);
            //Multiplication
            Vector2 &Multiply(const Vector2 &p_Vector);
            //Division
            Vector2 &Divide(const Vector2 &p_Vector);
            //+= Operator Override
            Vector2 &operator+=(const Vector2 &p_Vector);
            //-= Operator Override
            Vector2 &operator-=(const Vector2 &p_Vector);
            //*= Operator Override
            Vector2 &operator*=(const Vector2 &p_Vector);
            // /= Operator Override
            Vector2 &operator/=(const Vector2 &p_Vector);
            //== Operator Override
            bool operator==(const Vector2 &p_Vector);
            //!= Operator Override
            bool operator!=(const Vector2 &p_Vector);
            //+ Operator Override
            friend Vector2 operator+(Vector2 p_LValue, const Vector2 &p_RValue);
            //- Operator Override
            friend Vector2 operator-(Vector2 p_LValue, const Vector2 &p_RValue);
            //* Operator Override
            friend Vector2 operator*(Vector2 p_LValue, const Vector2 &p_RValue);
            // / Operator Override
            friend Vector2 operator/(Vector2 p_LValue, const Vector2 &p_RValue);
            //<< Operator Override
            friend std::ostream &operator<<(std::ostream &p_Stream, const Vector2 &p_Vector);
        };
    }
}