/*
 * Rudy Castan
 * Graphics Library
 * CS230
 */
#pragma once

#include "../../MathLibrary/MathLibrary.hpp"

class CameraSET
{
public:
    constexpr CameraSET() noexcept = default;
    CameraSET(Vector2<float> camera_center, Vector2<float> camera_up) noexcept;

    Vector2<float> GetCenter() const noexcept { return center; }
    void    SetCenter(Vector2<float> camera_center) noexcept { center = camera_center; }
    Vector2<float> GetUp() const noexcept { return up; }
    Vector2<float> GetRight() const noexcept { return right; }

    void ResetUp(Vector2<float> camera_up = { 0, 1 }) noexcept;

    void MoveUp(float distance) noexcept;
    void MoveRight(float distance) noexcept;
    void Rotate(float angle_radians) noexcept;

    Matrix3<float> CameraToWorld() const noexcept;
    Matrix3<float> WorldToCamera() const noexcept;

private:
    Vector2<float> center{};
    Vector2<float> up{ 0, 1 };
    Vector2<float> right{ 1, 0 };
};

