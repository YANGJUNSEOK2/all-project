/************************************************************************
*	File name : ParticleEngine.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author 
*			        Others
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once
#include "SpriteParticle.hpp"
#include <vector>

class SpriteParticle;
class SpriteBatch;

class ParticleEngine {
public:
    ParticleEngine();
    ~ParticleEngine();

    void addParticleBatch(SpriteParticle* particleBatch);

    void update(float deltaTime);

    void draw(SpriteBatch* spriteBatch);

private:
    std::vector<SpriteParticle*> m_batches;
};