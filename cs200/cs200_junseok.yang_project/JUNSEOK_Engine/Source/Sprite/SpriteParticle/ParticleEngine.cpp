/************************************************************************
*	File name : ParticleEngine.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author 
*			        Others 
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/
#include "ParticleEngine.hpp"
#include "SpriteParticle.hpp"
#include "../SpriteBatch/SpriteBatch.hpp"


ParticleEngine::ParticleEngine() 
{
}

ParticleEngine::~ParticleEngine()
{
    for (auto& b : m_batches)
    {
        delete b;
    }
}

void ParticleEngine::addParticleBatch(SpriteParticle* particleBatch) 
{
    m_batches.push_back(particleBatch);
}

void ParticleEngine::update(float deltaTime) {
    for (auto& b : m_batches) {
        b->update(deltaTime);
    }
}

void ParticleEngine::draw(SpriteBatch* spriteBatch) {
    for (auto& b : m_batches) {
        spriteBatch->Begin();
        b->draw(spriteBatch);
        spriteBatch->End();
        spriteBatch->SpriteRenderBatch();
    }
}
