#pragma once
#include <iostream>

namespace JS_Engine {
    namespace MathLibrary {
        struct Vector4 {
            //Components
            float XComponent;
            float YComponent;
            float ZComponent;
            float WComponent;

            Vector4();
            Vector4(const float &p_XValue, const float &p_YValue, const float &p_ZValue, const float &p_WValue);
            //Addition
            Vector4 &Add(const Vector4 &p_Vector);
            //Subtraction
            Vector4 &Subtract(const Vector4 &p_Vector);
            //Multiplication
            Vector4 &Multiply(const Vector4 &p_Vector);
            //Division
            Vector4 &Divide(const Vector4 &p_Vector);
            //+= Operator Override
            Vector4 &operator+=(const Vector4 &p_Vector);
            //-= Operator Override
            Vector4 &operator-=(const Vector4 &p_Vector);
            //*= Operator Override
            Vector4 &operator*=(const Vector4 &p_Vector);
            // /= Operator Override
            Vector4 &operator/=(const Vector4 &p_Vector);
            //== Operator Override
            bool operator==(const Vector4 &p_Vector);
            //!= Operator Override
            bool operator!=(const Vector4 &p_Vector);
            //+ Operator Override
            friend Vector4 operator+(Vector4 p_LValue, const Vector4 &p_RValue);
            //- Operator Override
            friend Vector4 operator-(Vector4 p_LValue, const Vector4 &p_RValue);
            //* Operator Override
            friend Vector4 operator*(Vector4 p_LValue, const Vector4 &p_RValue);
            // / Operator Override
            friend Vector4 operator/(Vector4 p_LValue, const Vector4 &p_RValue);
            //<< Operator Override
            friend std::ostream &operator<<(std::ostream &p_Stream, const Vector4 &p_Vector);
        };
    }
}