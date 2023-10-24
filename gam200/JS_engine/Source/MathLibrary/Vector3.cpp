#include "Vector3.hpp"

namespace JS_Engine {
    namespace MathLibrary {

        Vector3::Vector3() {
            XComponent = 0.0f;
            YComponent = 0.0f;
            ZComponent = 0.0f;
        }
        Vector3::Vector3(const float &p_XValue, const float &p_YValue, const float &p_ZValue) {
            this->XComponent = p_XValue;
            this->YComponent = p_YValue;
            this->ZComponent = p_ZValue;
        }

        Vector3 &Vector3::Add(const Vector3 &p_Vector) {
            XComponent += p_Vector.XComponent;
            YComponent += p_Vector.YComponent;
            ZComponent += p_Vector.ZComponent;
            return *this;
        }

        Vector3 &Vector3::Subtract(const Vector3 &p_Vector) {
            XComponent -= p_Vector.XComponent;
            YComponent -= p_Vector.YComponent;
            ZComponent -= p_Vector.ZComponent;
            return *this;
        }

        Vector3 &Vector3::Multiply(const Vector3 &p_Vector) {
            XComponent *= p_Vector.XComponent;
            YComponent *= p_Vector.YComponent;
            ZComponent *= p_Vector.ZComponent;
            return *this;
        }

        Vector3 &Vector3::Divide(const Vector3 &p_Vector) {
            XComponent /= p_Vector.XComponent;
            YComponent /= p_Vector.YComponent;
            ZComponent /= p_Vector.ZComponent;
            return *this;
        }

        Vector3 &Vector3::operator+=(const Vector3 &p_Vector) {
            return Add(p_Vector);
        }

        Vector3 &Vector3::operator-=(const Vector3 &p_Vector) {
            return Subtract(p_Vector);
        }

        Vector3 &Vector3::operator*=(const Vector3 &p_Vector) {
            return Multiply(p_Vector);
        }

        Vector3 &Vector3::operator/=(const Vector3 &p_Vector) {
            return Divide(p_Vector);
        }

        bool Vector3::operator==(const Vector3 &p_Vector) {
            return (XComponent == p_Vector.XComponent && YComponent == p_Vector.YComponent && ZComponent == p_Vector.ZComponent);
        }

        bool Vector3::operator!=(const Vector3 &p_Vector) {
            return !(*this == p_Vector);
        }

        Vector3 operator+(Vector3 p_LValue, const Vector3 &p_RValue) {
            return p_LValue.Add(p_RValue);
        }

        Vector3 operator-(Vector3 p_LValue, const Vector3 &p_RValue) {
            return p_LValue.Subtract(p_RValue);
        }

        Vector3 operator*(Vector3 p_LValue, const Vector3 &p_RValue) {
            return p_LValue.Multiply(p_RValue);
        }

        Vector3 operator/(Vector3 p_LValue, const Vector3 &p_RValue) {
            return p_LValue.Divide(p_RValue);
        }

        std::ostream &operator<<(std::ostream &p_Stream, const Vector3 &p_Vector) {
            p_Stream << "[Vector3] (" << p_Vector.XComponent << ", " << p_Vector.YComponent << ", " << p_Vector.ZComponent << ")";
            return p_Stream;
        }
    }
}