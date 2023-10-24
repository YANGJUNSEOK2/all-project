/*
junseok.yang
assignment5
cs230
spring 2019
*/
#include <CS230/graphics/Camera.hpp>
#include <CS230/math/angles.hpp>

namespace CS230
{
    Camera::Camera(vector2 camera_center, vector2 camera_up) noexcept
        :center(camera_center), up(camera_up), right(rotate_by(-HALF_PI, up))
    { }

    void Camera::ResetUp(vector2 camera_up) noexcept
    {
        up.x = camera_up.x;
        up.y = camera_up.y;
        right = { up.y , -up.x };
    }

    void Camera::MoveUp(float distance) noexcept
    {
        center += normalize(up)*distance;
    }

    void Camera::MoveRight(float distance) noexcept
    {
        center += normalize(right)*distance;
    }

    void Camera::Rotate(float angle_radians) noexcept
    {
        up = rotate_by(angle_radians, up);
        right = rotate_by(angle_radians, right);
    }

    matrix3 Camera::CameraToWorld() const noexcept
    {
        matrix3 cameraToWorld{
                 normalize(up).y, - normalize(up).x,0.0f,
                -normalize(right).y,normalize(right).x,0.0f,
                (normalize(right).y*dot(-normalize(up),center) - dot(-normalize(right),center)*normalize(up).y),
                (normalize(up).x*dot(-normalize(right),center) - dot(-normalize(up),center)*normalize(right).x),
                1.0f
               };

        return cameraToWorld;
    }

    matrix3 Camera::WorldToCamera() const noexcept
    {
        matrix3 worldToCamera {
            normalize(right).x,normalize(up).x,0.0f,
            normalize(right).y,normalize(up).y,0.0f,
            (dot(-normalize(right),center)),(dot(-normalize(up),center)),1.0f 
        };
        return worldToCamera;
    }

}
