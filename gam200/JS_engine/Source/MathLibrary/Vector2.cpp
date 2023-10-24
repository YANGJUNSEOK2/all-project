#include "Vector2.hpp"

namespace JS_Engine {
    namespace MathLibrary {
        
        Vector2::Vector2() {
            XComponent = 0.0f;
            YComponent = 0.0f;
        }
        Vector2::Vector2(const float &p_XValue, const float &p_YValue) {
            this->XComponent = p_XValue;
            this->YComponent = p_YValue;
        }

        Vector2 &Vector2::Add(const Vector2 &p_Vector) {
            XComponent += p_Vector.XComponent;
            YComponent += p_Vector.YComponent;
            return *this;
        }

        Vector2 &Vector2::Subtract(const Vector2 &p_Vector) {
            XComponent -= p_Vector.XComponent;
            YComponent -= p_Vector.YComponent;
            return *this;
        }

        Vector2 &Vector2::Multiply(const Vector2 &p_Vector) {
            XComponent *= p_Vector.XComponent;
            YComponent *= p_Vector.YComponent;
            return *this;
        }

        Vector2 &Vector2::Divide(const Vector2 &p_Vector) {
            XComponent /= p_Vector.XComponent;
            YComponent /= p_Vector.YComponent;
            return *this;
        }

        Vector2 &Vector2::operator+=(const Vector2 &p_Vector) {
            return Add(p_Vector);
        }

        Vector2 &Vector2::operator-=(const Vector2 &p_Vector) {
            return Subtract(p_Vector);
        }

        Vector2 &Vector2::operator*=(const Vector2 &p_Vector) {
            return Multiply(p_Vector);
        }

        Vector2 &Vector2::operator/=(const Vector2 &p_Vector) {
            return Divide(p_Vector);
        }

        bool Vector2::operator==(const Vector2 &p_Vector) {
            return (XComponent == p_Vector.XComponent && YComponent == p_Vector.YComponent);
        }

        bool Vector2::operator!=(const Vector2 &p_Vector) {
            return !(*this == p_Vector);
        }

        Vector2 operator+(Vector2 p_LValue, const Vector2 &p_RValue) {
            return p_LValue.Add(p_RValue);
        }

        Vector2 operator-(Vector2 p_LValue, const Vector2 &p_RValue) {
            return p_LValue.Subtract(p_RValue);
        }

        Vector2 operator*(Vector2 p_LValue, const Vector2 &p_RValue) {
            return p_LValue.Multiply(p_RValue);
        }

        Vector2 operator/(Vector2 p_LValue, const Vector2 &p_RValue) {
            return p_LValue.Divide(p_RValue);
        }

        std::ostream &operator<<(std::ostream &p_Stream, const Vector2 &p_Vector) {
            p_Stream << "[Vector2] (" << p_Vector.XComponent << ", " << p_Vector.YComponent << ")";
            return p_Stream;
        }
    }
}