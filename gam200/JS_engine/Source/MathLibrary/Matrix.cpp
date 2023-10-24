#include "Matrix.hpp"

namespace JS_Engine {
    namespace MathLibrary {
        
        Matrix::Matrix() {
            for (int i = 0; i < 4 * 4; i++) {
                Elements[i] = 0.0f;
            }
        }
        Matrix::Matrix(float p_Diagonal) {
            for (int i = 0; i < 4 * 4; i++) {
                Elements[i] = 0.0f;
            }
            Elements[0 + 0 * 4] = p_Diagonal;
            Elements[1 + 1 * 4] = p_Diagonal;
            Elements[2 + 2 * 4] = p_Diagonal;
            Elements[3 + 3 * 4] = p_Diagonal;
        }
        
        Vector2 Matrix::Multiply(const Vector2 &p_Vector) const {
            return Vector2(
                Column[0].XComponent * p_Vector.XComponent + Column[1].XComponent * p_Vector.YComponent + Column[2].XComponent + Column[3].XComponent,
                Column[0].YComponent * p_Vector.XComponent + Column[1].YComponent * p_Vector.YComponent + Column[2].YComponent + Column[3].YComponent
            );
        }
        Vector3 Matrix::Multiply(const Vector3 &p_Vector) const {
            return Vector3(
                Column[0].XComponent * p_Vector.XComponent + Column[1].XComponent * p_Vector.YComponent + Column[2].XComponent * p_Vector.ZComponent + Column[3].XComponent,
                Column[0].YComponent * p_Vector.XComponent + Column[1].YComponent * p_Vector.YComponent + Column[2].YComponent * p_Vector.ZComponent + Column[3].YComponent,
                Column[0].ZComponent * p_Vector.XComponent + Column[1].ZComponent * p_Vector.YComponent + Column[2].ZComponent * p_Vector.ZComponent + Column[3].ZComponent
            );
        }
        Vector4 Matrix::Multiply(const Vector4 &p_Vector) const {
            return Vector4(
                Column[0].XComponent * p_Vector.XComponent + Column[1].XComponent * p_Vector.YComponent + Column[2].XComponent * p_Vector.ZComponent + Column[3].XComponent * p_Vector.WComponent,
                Column[0].YComponent * p_Vector.XComponent + Column[1].YComponent * p_Vector.YComponent + Column[2].YComponent * p_Vector.ZComponent + Column[3].YComponent * p_Vector.WComponent,
                Column[0].ZComponent * p_Vector.XComponent + Column[1].ZComponent * p_Vector.YComponent + Column[2].ZComponent * p_Vector.ZComponent + Column[3].ZComponent * p_Vector.WComponent,
                Column[0].WComponent * p_Vector.XComponent + Column[1].WComponent * p_Vector.YComponent + Column[2].WComponent * p_Vector.ZComponent + Column[3].WComponent * p_Vector.WComponent
            );
        }
        Matrix &Matrix::Multiply(const Matrix  &p_Matrix) {
            float MatrixData[16];
            for (int Row = 0; Row < 4; Row++) {
                for (int Column = 0; Column < 4; Column++) {
                    float Sum = 0.0f;
                    for (int Component = 0; Component < 4; Component++) {
                        Sum += Elements[Column + Component * 4] * p_Matrix.Elements[Component + Row * 4];
                    }
                    MatrixData[Column + Row * 4] = Sum;
                }
            }
            memcpy(Elements, MatrixData, 4 * 4 * sizeof(float));
            return *this;
        }
        
        Matrix &Matrix::operator*=(const Matrix &p_Matrix) {
            return Multiply(p_Matrix);
        }
        
        Vector2 operator*(const Matrix &p_LValue, const Vector2 &p_RValue) {
            return p_LValue.Multiply(p_RValue);
        }
        Vector3 operator*(const Matrix &p_LValue, const Vector3 &p_RValue) {
            return p_LValue.Multiply(p_RValue);
        }
        Vector4 operator*(const Matrix &p_LValue, const Vector4 &p_RValue) {
            return p_LValue.Multiply(p_RValue);
        }
        Matrix operator*(Matrix p_LValue, const Matrix &p_RValue) {
            return p_LValue.Multiply(p_RValue);
        }
       
        Matrix Matrix::Identiy() {
            return Matrix(1.0f);
        }
        
        Matrix Matrix::Orthographic(float p_Left, float p_Right, float p_Bottom, float p_Top, float p_Near, float p_Far) {
            Matrix Result(1.0f);

            Result.Elements[0 + 0 * 4] = 2.0f / (p_Right - p_Left);
            Result.Elements[1 + 1 * 4] = 2.0f / (p_Top - p_Bottom);
            Result.Elements[2 + 2 * 4] = 2.0f / (p_Near - p_Far);

            Result.Elements[0 + 3 * 4] = (p_Left + p_Right) / (p_Left - p_Right);
            Result.Elements[1 + 3 * 4] = (p_Bottom + p_Top) / (p_Bottom - p_Top);
            Result.Elements[2 + 3 * 4] = (p_Far + p_Near) / (p_Far - p_Near);
            return Result;
        }
       
        Matrix Matrix::Perspective(float p_FieldOfView, float p_AspectRatio, float p_Near, float p_Far) {
            Matrix Result(1.0f);

            float ValueQ = 1.0f / tan(DegreeToRadian(0.5f * p_FieldOfView));
            float ValueA = ValueQ / p_AspectRatio;
            float ValueB = (p_Near + p_Far) / (p_Near - p_Far);
            float ValueC = (2.0f * p_Near * p_Far) / (p_Near - p_Far);

            Result.Elements[0 + 0 * 4] = ValueA;
            Result.Elements[1 + 1 * 4] = ValueQ;
            Result.Elements[2 + 2 * 4] = ValueB;
            Result.Elements[3 + 2 * 4] = -1.0f;
            Result.Elements[2 + 3 * 4] = ValueC;
            return Result;
        }
        
        Matrix Matrix::Rotate(float p_Angle, const Vector3 &p_Axis) {
            Matrix Result(1.0f);

            float ValueX = p_Axis.XComponent;
            float ValueY = p_Axis.YComponent;
            float ValueZ = p_Axis.ZComponent;
            float ValueRadian = DegreeToRadian(p_Angle);
            float ValueSine = sin(ValueRadian);
            float ValueCosine = cos(ValueRadian);
            float OneMinusCosine = 1.0f - ValueCosine;

            Result.Elements[0 + 0 * 4] = ValueX * OneMinusCosine + ValueCosine;
            Result.Elements[1 + 0 * 4] = ValueX * ValueY * OneMinusCosine + ValueZ * ValueSine;
            Result.Elements[2 + 0 * 4] = ValueX * ValueZ * OneMinusCosine - ValueY * ValueSine;

            Result.Elements[0 + 1 * 4] = ValueX * ValueY * OneMinusCosine - ValueZ * ValueSine;
            Result.Elements[1 + 1 * 4] = ValueY * OneMinusCosine + ValueCosine;
            Result.Elements[2 + 1 * 4] = ValueY * ValueZ * OneMinusCosine + ValueX * ValueSine;

            Result.Elements[0 + 2 * 4] = ValueX * ValueZ * OneMinusCosine + ValueY * ValueSine;
            Result.Elements[1 + 2 * 4] = ValueY * ValueZ * OneMinusCosine - ValueX * ValueSine;
            Result.Elements[2 + 2 * 4] = ValueZ * OneMinusCosine + ValueCosine;
            return Result;
        }
        
        Matrix Matrix::Translate(const Vector3 &p_Translation) {
            Matrix Result(1.0f);

            Result.Elements[0 + 3 * 4] = p_Translation.XComponent;
            Result.Elements[1 + 3 * 4] = p_Translation.YComponent;
            Result.Elements[2 + 3 * 4] = p_Translation.ZComponent;
            return Result;
        }
        
        Matrix Matrix::Scale(const Vector3 &p_Scale) {
            Matrix Result(1.0f);

            Result.Elements[0 + 0 * 4] = p_Scale.XComponent;
            Result.Elements[1 + 1 * 4] = p_Scale.YComponent;
            Result.Elements[2 + 2 * 4] = p_Scale.ZComponent;
            return Result;
        }
    }
}