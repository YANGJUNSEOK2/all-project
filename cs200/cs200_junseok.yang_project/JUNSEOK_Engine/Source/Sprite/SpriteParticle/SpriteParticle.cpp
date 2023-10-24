/************************************************************************
*	File name : SpriteParticle.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author
*			        Others
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/
#include "SpriteParticle.hpp"

SpriteParticle::SpriteParticle() 
{
}

SpriteParticle::~SpriteParticle() 
{
    delete[] m_particles;
}

void SpriteParticle::init(int maxParticles,float decayRate,GLTexture texture,std::function<void(Particle&, float)> updateFunc) {
    m_maxParticles = maxParticles;
    m_particles = new Particle[maxParticles];
    m_decayRate = decayRate;
    m_texture = texture;
    m_updateFunc = updateFunc;
}

void SpriteParticle::update(float deltaTime) {
    for (int i = 0; i < m_maxParticles; i++) {

        if (m_particles[i].life > 0.0f) 
        {
            m_updateFunc(m_particles[i], deltaTime);
            m_particles[i].life -= m_decayRate * deltaTime;
        }
    }
}

void SpriteParticle::draw(SpriteBatch* spriteBatch) {
    Vector4<float> uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    for (int i = 0; i < m_maxParticles; i++) {

        auto& p = m_particles[i];
        if (p.life > 0.0f) {
            Vector4<float> destRect(p.position.x, p.position.y, p.width, p.width);
            spriteBatch->Draw(destRect, uvRect, m_texture.id, 0.0f, p.color);
        }
    }
}

void SpriteParticle::addParticle(const Vector2<float>& position,
    const Vector2<float>& velocity,
    const Color& color,
    float width) {
    int particleIndex = FreeParticleNum();

    auto& p = m_particles[particleIndex];

    p.life = 1.0f;
    p.position = position;
    p.velocity = velocity;
    p.color = color;
    p.width = width;
}

int SpriteParticle::FreeParticleNum() {

    for (int i = m_lastFreeParticle; i < m_maxParticles; i++) {
        if (m_particles[i].life <= 0.0f) {
            m_lastFreeParticle = i;
            return i;
        }
    }
    for (int i = 0; i < m_lastFreeParticle; i++) {
        if (m_particles[i].life <= 0.0f) {
            m_lastFreeParticle = i;
            return i;
        }
    }

    return 0;
}
