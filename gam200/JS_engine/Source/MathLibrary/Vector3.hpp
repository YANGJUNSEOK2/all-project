#pragma once
#include <iostream>

namespace JS_Engine {
    namespace MathLibrary {
        struct Vector3 {
            //Components
            float XComponent;
            float YComponent;
            float ZComponent;

            Vector3();
            Vector3(const float &p_XValue, const float &p_YValue, const float &p_ZValue);
            //Addition
            Vector3 &Add(const Vector3 &p_Vector);
            //Subtraction
            Vector3 &Subtract(const Vector3 &p_Vector);
            //Multiplication
            Vector3 &Multiply(const Vector3 &p_Vector);
            //Division
            Vector3 &Divide(const Vector3 &p_Vector);
            //+= Operator Override
            Vector3 &operator+=(const Vector3 &p_Vector);
            //-= Operator Override
            Vector3 &operator-=(const Vector3 &p_Vector);
            //*= Operator Override
            Vector3 &operator*=(const Vector3 &p_Vector);
            // /= Operator Override
            Vector3 &operator/=(const Vector3 &p_Vector);
            //== Operator Override
            bool operator==(const Vector3 &p_Vector);
            //!= Operator Override
            bool operator!=(const Vector3 &p_Vector);
            //+ Operator Override
            friend Vector3 operator+(Vector3 p_LValue, const Vector3 &p_RValue);
            //- Operator Override
            friend Vector3 operator-(Vector3 p_LValue, const Vector3 &p_RValue);
            //* Operator Override
            friend Vector3 operator*(Vector3 p_LValue, const Vector3 &p_RValue);
            // / Operator Override
            friend Vector3 operator/(Vector3 p_LValue, const Vector3 &p_RValue);
            //<< Operator Override
            friend std::ostream &operator<<(std::ostream &p_Stream, const Vector3 &p_Vector);
        };
    }
}