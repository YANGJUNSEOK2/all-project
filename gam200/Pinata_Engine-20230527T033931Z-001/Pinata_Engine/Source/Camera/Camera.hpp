/************************************************************************
*	File name : Camera.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester
*************************************************************************/
#pragma once
#include "../MathLibrary/MathLibrary.hpp"
#include "../Camera/CameraSet/CameraSet.hpp"
#include "../Camera/CameraSet/CameraView.hpp"
#include "../Camera/CameraSet/Transform.hpp"

class Camera
{
public:
    Camera();
    Camera(Vector2<float> camera_center, Vector2<float> camera_up);
    ~Camera();

    void InitCamera(int p_ScreenWidth, int p_ScreenHeight);
    void UpdateCamera();

    Vector2<float> ScreenToWorld(Vector2<float> screenCoords);

    void SetPosition(const Vector2<float>& p_Position) { m_Position = p_Position; }

    void SetViewSize(Vector2<float> pixel_size) noexcept;

    void SetViewSize(int new_pixel_width, int new_pixel_height) noexcept;

    void SetScale(float p_Scale) { m_Scale = p_Scale; }

    void SetRotation(float p_Rotation) { m_Rotation = p_Rotation; }

    Vector2<float> GetPosition() { return m_Position; }

    float GetRotation() { return m_Rotation; }

    float GetScale() { return m_Scale; }

    Matrix3<float> GetCameraOrtho() { return m_CameraMatrix; }

    void CameraTranslation(float X, float Y);

    void SetCameraZoom(float p_ZoomSize);

    void CameraRotation(float p_Angle);
private:
    int m_ScreenWidth, m_ScreenHeight;
    bool m_MatrixChange;
    float m_Scale;
    float m_Rotation;

    Vector2<float> m_Position;
    Matrix3<float> m_CameraMatrix;
    Matrix3<float> m_Ortho;

    CameraSET m_CameraSet;
    CameraView m_CameraView;
    Transform m_CameraTrans;
};
