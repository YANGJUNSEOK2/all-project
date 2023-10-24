/************************************************************************
*	File name : Level1.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include "StateManager.h"
#include "../Camera/Camera.hpp"
#include "../Mesh/MeshDraw.hpp"
#include "../Texture/ImageLoader.hpp"
#include "../Texture/ImageTexture.hpp"
#include "../Texture/ScreenShot.hpp"

class Level1 : public GameState
{
public:

    Level1() = default;
    void Init(Engine* game) override;
    void Close(Engine* game) override;

    void Pause() override;
    void Resume() override;

    void Update(Engine* game) override;
    void Draw(Engine* game) override;


    // Implement Singleton Pattern
    static Level1* Instance()
    {
        return &m_Level1;
    }
    ~Level1() = default;
protected:


private:

    MeshDraw m_Mesh;

    static Level1 m_Level1;
    FPS m_fpslimiter;
    float m_MaxFPS = 0;
    float m_FPS = 0;

    Camera m_Camera;

    const float radians_per_second = PI / 500.0f;
    float cameraRotateDirection = 0;

    Matrix3<float> m_BoxPosition = build_translation<float>(0.f, -400.f); //transform
    Matrix3<float> m_BoxAngle = build_rotation<float>(1.f); //rotate
    Matrix3<float> m_BoxWH = build_scale<float>(200.f, 200.f); //scale

    Matrix3<float> m_Box2Position = build_translation<float>(-600.f, 200.f);
    Matrix3<float> m_Box2Angle = build_rotation<float>(1.f);
    Matrix3<float> m_Box2WH = build_scale<float>(200.f, 70.f);

    Matrix3<float> m_CirclePosition = build_translation<float>(500.f, -400.f);
    Matrix3<float> m_CircleAngle = build_rotation<float>(1.f);
    Matrix3<float> m_CircleWH = build_scale<float>(100.f, 100.f);

    Matrix3<float> m_Circle2Position = build_translation<float>(-100.f, 200.f);
    Matrix3<float> m_Circle2Angle = build_rotation<float>(1.f);
    Matrix3<float> m_Circle2WH = build_scale<float>(100.f, 50.f);

    Matrix3<float> m_TrianglePosition = build_translation<float>(0.f, 0.f);
    Matrix3<float> m_TriangleAngle = build_rotation<float>(1.f);
    Matrix3<float> m_TriangleWH = build_scale<float>(200.f, 100.f);

    Matrix3<float> m_Triangle2Position = build_translation<float>(-300.f, -200.f);
    Matrix3<float> m_Triangle2Angle = build_rotation<float>(1.f);
    Matrix3<float> m_Triangle2WH = build_scale<float>(150.f, 150.f);

    Matrix3<float> m_LinePosition = build_translation<float>(300, 200);
    Matrix3<float> m_LineAngle = build_rotation<float>(1.f);
    Matrix3<float> m_LineWH = build_scale<float>(400, 400);
   
    Matrix3<float> Hierarchical = build_identity<float>();
};
