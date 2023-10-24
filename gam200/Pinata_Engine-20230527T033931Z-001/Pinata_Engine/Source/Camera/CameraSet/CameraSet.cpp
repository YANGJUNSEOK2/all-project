/*
junseok.yang
assignment5
cs230
spring 2019
*/
#include "CameraSet.hpp"

CameraSET::CameraSET(Vector2<float> camera_center, Vector2<float> camera_up) noexcept
    :center(camera_center), up(camera_up)
{
    right = rotate_By(-PI / 4.0f, up);
}

void CameraSET::ResetUp(Vector2<float> camera_up) noexcept
{
    up.x = camera_up.x;
    up.y = camera_up.y;
    right = { up.y , -up.x };
}

void CameraSET::MoveUp(float distance) noexcept
{
    center += normalize(up)*distance;
}

void CameraSET::MoveRight(float distance) noexcept
{
    center += normalize(right)*distance;
}

void CameraSET::Rotate(float angle_radians) noexcept
{
    up = rotate_By(angle_radians, up);
    right = rotate_By(angle_radians, right);
}

Matrix3<float> CameraSET::CameraToWorld() const noexcept
{
    Matrix3<float> cameraToWorldMatrix;
    cameraToWorldMatrix.Column[0] = { right.x, up.x, center.x };
    cameraToWorldMatrix.Column[1] = { right.y, up.y, center.y };
    cameraToWorldMatrix.Column[2] = { 0, 0 ,1 };
    return cameraToWorldMatrix;
}

Matrix3<float> CameraSET::WorldToCamera() const noexcept
{
    Matrix3<float> WorldToCameraMatrix;
    WorldToCameraMatrix.Column[0] = { normalize(right).x, normalize(right).y, (dot(-normalize(right), center)) };
    WorldToCameraMatrix.Column[1] = { normalize(up).x, normalize(up).y, (dot(-normalize(up), center)) };
    WorldToCameraMatrix.Column[2] = { 0.0f, 0.0f, 1.0f };
    return WorldToCameraMatrix;
}


