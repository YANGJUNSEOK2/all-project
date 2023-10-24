/************************************************************************
*	File name : FPS.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester
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

    private:
        void CalculateFPS();

        float m_FPS;
        float m_FrameTime;
        float m_MaxFPS;
        unsigned int m_StartPoint;
    };
