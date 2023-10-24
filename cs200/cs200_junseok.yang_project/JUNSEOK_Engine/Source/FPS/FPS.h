/************************************************************************
*	File name : FPS.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once

    class FPS
    {
    public:
        FPS();
        ~FPS() = default;

        void Init(float p_MaxFPS);
        void SetMaxFPS(float p_MaxFPS);
        void Begin();
        float End();

        void setFPS(float p_FPS) { m_FPS = p_FPS; }
        float getFPS() { return m_FPS; }

    private:
        void CalculateFPS();

        float m_FPS;
        float m_FrameTime;
        float m_MaxFPS;
        unsigned int m_StartPoint;
    };
