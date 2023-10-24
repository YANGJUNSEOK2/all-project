/************************************************************************
*	File name : Camera.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/

#include "Camera.hpp"

Camera::Camera() :m_Position(0.0f, 0.0f), m_Scale(1.0),
m_MatrixChange(true), m_ScreenWidth(500),
m_ScreenHeight(500),
m_Rotation(0.0f)
{
}

Camera::~Camera()
{
}

void Camera::InitCamera(int p_ScreenWidth, int p_ScreenHeight)
{
    m_ScreenWidth = p_ScreenWidth;
    m_ScreenHeight = p_ScreenHeight;
    m_Scale = 1.0f;
    m_Position = { 0.0f,0.0f };
    m_Rotation = 0.0f;
    m_CameraTrans.SetTranslation(m_Position);
    m_CameraSet.Rotate(m_Rotation);
    m_CameraSet.GetUp() = { 0.0f,0.0f };
    m_CameraSet.GetRight() = { 0.0f,0.0f };
    m_CameraMatrix = m_CameraSet.WorldToCamera();
    m_CameraView.SetViewSize(p_ScreenWidth, p_ScreenHeight);
}

void Camera::UpdateCamera()
{
    m_CameraTrans.SetTranslation(m_Position);
    m_CameraSet.Rotate(m_Rotation);
    m_CameraView.SetViewSize(m_ScreenWidth * 2, m_ScreenHeight * 2);
    m_CameraView.SetZoom(m_Scale);

    m_CameraMatrix = m_CameraView.GetCameraToNDCTransform() * m_CameraSet.WorldToCamera() * m_CameraTrans.GetModelToWorld();
}

void Camera::CameraTranslation(float X, float Y)
{
    SetPosition(GetPosition() + Vector2<float>{X, Y});
}

void Camera::SetCameraZoom(float p_ZoomSize)
{
    SetScale(GetScale() + p_ZoomSize);
}

void Camera::CameraRotation(float p_Angle)
{
    SetRotation(p_Angle);
}
