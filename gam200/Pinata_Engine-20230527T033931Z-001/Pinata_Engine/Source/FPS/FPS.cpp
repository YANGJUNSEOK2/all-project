/************************************************************************
*	File name : FPS.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	2019 Fall Semester
*************************************************************************/
#include "FPS.h"
#include <SDL.h>

    FPS::FPS() : m_FPS(0), m_FrameTime(0), m_MaxFPS(0), m_StartPoint(0) {}

    void FPS::Init(float p_MaxFPS)
    {
        SetMaxFPS(p_MaxFPS);
    }

    void FPS::SetMaxFPS(float p_MaxFPS)
    {
        m_MaxFPS = p_MaxFPS;
    }

    void FPS::Begin()
    {
        m_StartPoint = SDL_GetTicks();
    }

    float FPS::End()
    {
        CalculateFPS();

        float frame = static_cast<float>(SDL_GetTicks() - m_StartPoint);
        //LIMIT the FPS to the max FPS
        if (1000.0f / m_MaxFPS > frame)
        {
            SDL_Delay(static_cast<Uint32>(1000.0f / m_MaxFPS - frame));
        }

        return m_FPS;
    }

    void FPS::CalculateFPS()
    {
        static const int NUM = 100;
        static float frameTimes[NUM];
        static int currFrame = 0;

        static float p_Prev = static_cast<float>(SDL_GetTicks());

        float p_Curr;
        p_Curr = static_cast<float>(SDL_GetTicks());

        m_FrameTime = p_Curr - p_Prev;
        frameTimes[currFrame % NUM] = m_FrameTime;

        p_Prev = p_Curr;

        currFrame++;

        int count;
        if (currFrame < NUM)
        {
            count = currFrame;
        }
        else
        {
            count = NUM;
        }

        float timeAverage = 0;
        for (int i = 0; i < count; i++)
        {
            timeAverage += frameTimes[i];
        }
        timeAverage /= count;

        if (timeAverage > 0)
        {
            m_FPS = 1000.0f / timeAverage;
        }
        else
        {
            m_FPS = 60.0f;
        }
    }
