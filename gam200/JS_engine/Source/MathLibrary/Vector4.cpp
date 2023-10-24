#include "Vector4.hpp"

namespace JS_Engine {
    namespace MathLibrary {

        Vector4::Vector4() {
            XComponent = 0.0f;
            YComponent = 0.0f;
            ZComponent = 0.0f;
            WComponent = 0.0f;
        }

        Vector4::Vector4(const float &p_XValue, const float &p_YValue, const float &p_ZValue, const float &p_WValue) {
            this->XComponent = p_XValue;
            this->YComponent = p_YValue;
            this->ZComponent = p_ZValue;
            this->WComponent = p_WValue;
        }

        Vector4 &Vector4::Add(const Vector4 &p_Vector) {
            XComponent += p_Vector.XComponent;
            YComponent += p_Vector.YComponent;
            ZComponent += p_Vector.ZComponent;
            WComponent += p_Vector.WComponent;
            return *this;
        }

        Vector4 &Vector4::Subtract(const Vector4 &p_Vector) {
            XComponent -= p_Vector.XComponent;
            YComponent -= p_Vector.YComponent;
            ZComponent -= p_Vector.ZComponent;
            WComponent -= p_Vector.WComponent;
            return *this;
        }

        Vector4 &Vector4::Multiply(const Vector4 &p_Vector) {
            XComponent *= p_Vector.XComponent;
            YComponent *= p_Vector.YComponent;
            ZComponent *= p_Vector.ZComponent;
            WComponent *= p_Vector.WComponent;
            return *this;
        }

        Vector4 &Vector4::Divide(const Vector4 &p_Vector) {
            XComponent /= p_Vector.XComponent;
            YComponent /= p_Vector.YComponent;
            ZComponent /= p_Vector.ZComponent;
            WComponent /= p_Vector.WComponent;
            return *this;
        }

        Vector4 &Vector4::operator+=(const Vector4 &p_Vector) {
            return Add(p_Vector);
        }

        Vector4 &Vector4::operator-=(const Vector4 &p_Vector) {
            return Subtract(p_Vector);
        }

        Vector4 &Vector4::operator*=(const Vector4 &p_Vector) {
            return Multiply(p_Vector);
        }

        Vector4 &Vector4::operator/=(const Vector4 &p_Vector) {
            return Divide(p_Vector);
        }
        bool Vector4::operator==(const Vector4 &p_Vector) {
            return (XComponent == p_Vector.XComponent && YComponent == p_Vector.YComponent && ZComponent == p_Vector.ZComponent && WComponent == p_Vector.WComponent);
        }

        bool Vector4::operator!=(const Vector4 &p_Vector) {
            return !(*this == p_Vector);
        }

        Vector4 operator+(Vector4 p_LValue, const Vector4 &p_RValue) {
            return p_LValue.Add(p_RValue);
        }

        Vector4 operator-(Vector4 p_LValue, const Vector4 &p_RValue) {
            return p_LValue.Subtract(p_RValue);
        }

        Vector4 operator*(Vector4 p_LValue, const Vector4 &p_RValue) {
            return p_LValue.Multiply(p_RValue);
        }

        Vector4 operator/(Vector4 p_LValue, const Vector4 &p_RValue) {
            return p_LValue.Divide(p_RValue);
        }

        std::ostream &operator<<(std::ostream &p_Stream, const Vector4 &p_Vector) {
            p_Stream << "[Vector4] (" << p_Vector.XComponent << ", " << p_Vector.YComponent << ", " << p_Vector.ZComponent << ", " << p_Vector.WComponent << ")";
            return p_Stream;
        }
    }
}