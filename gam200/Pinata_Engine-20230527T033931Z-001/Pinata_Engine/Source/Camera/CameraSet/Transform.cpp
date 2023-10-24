/*
junseok.yang
assignment5
cs230
spring 2019
*/
#include "Transform.hpp"
#include "../../MathLibrary/MathLibrary.hpp"


Matrix3<float> Transform::GetModelToWorld() const noexcept
{
    Matrix3<float> matrix_r = build_rotation<float>(GetRotation());
    Matrix3<float> matrix_s = build_scale<float>(GetScale().x, GetScale().y);
    Matrix3<float> matrix_t = build_translation<float>(GetTranslation().x, GetTranslation().y);
    Matrix3<float> matrix_trs = matrix_t * matrix_r * matrix_s;
    if (parent != nullptr)
    {
        parent->GetModelToWorld() * matrix_trs;
    }
    return matrix_trs;
}
Matrix3<float> Transform::GetWorldToModel() const noexcept
{
    Matrix3<float> matrix_srt;
    Matrix3<float> matrix_r = build_rotation<float>(-GetRotation());
    Matrix3<float> matrix_s = build_scale<float>(1.0f / GetScale().x, 1.0f / GetScale().y);
    Matrix3<float> matrix_t = build_translation<float>(-GetTranslation().x, -GetTranslation().y);
    matrix_srt = matrix_s * matrix_r * matrix_t;
    if (parent != nullptr)
    {
        parent->GetWorldToModel() * matrix_srt;
    }
    return matrix_srt;
}
float Transform::CalculateWorldDepth() const noexcept
{
    float add_depth = 0;
    add_depth = depth;
    if (parent != nullptr)
    {
        return add_depth + parent->CalculateWorldDepth();
    }
    return add_depth;
}
float Transform::GetDepth() const noexcept
{
    return depth;
}
void Transform::SetDepth(float new_depth) noexcept
{
    depth = new_depth;
}
Vector2<float> Transform::GetTranslation() const noexcept
{
    return translation;
}
void Transform::SetTranslation(const Vector2<float>& new_translation) noexcept
{
    translation = new_translation;
}
Vector2<float> Transform::GetScale() const noexcept
{
    return scale;
}
void Transform::SetScale(const Vector2<float>& new_scale) noexcept
{
    scale = new_scale;
}
float Transform::GetRotation() const noexcept
{
    return rotation;
}
void  Transform::SetRotation(float new_rotation) noexcept
{
    rotation = new_rotation;
}
const Transform* Transform::GetParent() const noexcept
{
    return parent;
}
void Transform::SetParent(const Transform* transform_parent) noexcept
{
    parent = transform_parent;
}
