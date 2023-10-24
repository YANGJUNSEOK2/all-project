/*
junseok.yang
assignment5
cs230
spring 2019
*/
#include <CS230/graphics/Transform.hpp>

namespace CS230
{
    matrix3 Transform::GetModelToWorld() const noexcept
    {
        matrix3 getModelToWorld = MATRIX3::build_identity();
        matrix3 matrix_r = MATRIX3::build_rotation(GetRotation());
        matrix3 matrix_s = MATRIX3::build_scale(GetScale());
        matrix3 matrix_t = MATRIX3::build_translation(GetTranslation());
        matrix3 matrix_trs = matrix_t * matrix_r * matrix_s;
        if (parent != nullptr)
        {
            getModelToWorld = parent->GetModelToWorld();
        }
        return getModelToWorld*matrix_trs;
    }
    matrix3 Transform::GetWorldToModel() const noexcept
    {
        matrix3 getWorldToModel = MATRIX3::build_identity();
        matrix3 matrix_r = MATRIX3::build_rotation(-GetRotation());
        matrix3 matrix_s = MATRIX3::build_scale(1.0f/scale.x,1.0f/scale.y);
        matrix3 matrix_t = MATRIX3::build_translation(-GetTranslation());
        matrix3 matrix_srt = matrix_s * matrix_r * matrix_t;
        if (parent != nullptr)
        {
            getWorldToModel=parent->GetWorldToModel();
        }
        return matrix_srt * getWorldToModel;
    }
    float Transform::CalculateWorldDepth() const noexcept
    {
        float add_depth =0;
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
    vector2 Transform::GetTranslation() const noexcept
    {
        return translation;
    }
    void Transform::SetTranslation(const vector2& new_translation) noexcept
    {
        translation = new_translation;
    }
    vector2 Transform::GetScale() const noexcept
    {
        return scale;
    }
    void Transform::SetScale(const vector2& new_scale) noexcept
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
}
