/************************************************************************
*	File name : Level3.hpp
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
#include "../Sprite/SpriteParticle/ParticleEngine.hpp"
#include "../Sprite/SpriteParticle/SpriteParticle.hpp"

class Level3 : public GameState
{
public:

    Level3() = default;
    void Init(Engine* game) override;
    void Close(Engine* game) override;

    void Pause() override;
    void Resume() override;

    void Update(Engine* game) override;
    void Draw(Engine* game) override;

    // Implement Singleton Pattern
    static Level3* Instance()
    {
        return &m_Level3;
    }
    ~Level3() = default;
protected:


private:
    static Level3 m_Level3;

    SpriteBatch Text;
    SpriteBatch Ani;

    ParticleEngine m_particleEngine;
    SpriteParticle* m_ParticleBatch;
    SpriteBatch A;
    std::vector<SpriteBatch> B;
    std::wstring fpsText{};
    FPS m_fpslimiter;
    float m_MaxFPS = 0;
    float m_FPS = 0;

};
