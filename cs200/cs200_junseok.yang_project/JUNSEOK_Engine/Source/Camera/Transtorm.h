/************************************************************************
*	File name : Transform.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include "../MathLibrary/MathLibrary.hpp"

class Transform
{
public:
    Transform() noexcept = default;
    Matrix3<float> GetModelToWorld() const noexcept;
    Matrix3<float> GetWorldToModel() const noexcept;

    float CalculateWorldDepth() const noexcept;
    float GetDepth() const noexcept;
    void  SetDepth(float new_depth) noexcept;

    Vector2<float> GetTranslation() const noexcept;
    void    SetTranslation(const Vector2<float>& new_translation) noexcept;

    Vector2<float> GetScale() const noexcept;
    void    SetScale(const Vector2<float>& new_scale) noexcept;

    float GetRotation() const noexcept;
    void  SetRotation(float new_rotation) noexcept;

    const Transform* GetParent() const noexcept;
    void             SetParent(const Transform* transform_parent) noexcept;

private:
    Vector2<float>          translation{};
    Vector2<float>          scale{ 1.0f, 1.0f };
    float            rotation = 0.0f;
    float            depth = 0.0f;
    const Transform* parent = nullptr;
};
