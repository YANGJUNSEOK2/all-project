/************************************************************************
*	File name : SpriteParticle.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author
*			        Others
*
*	File description :
*	2019 Fall Semester cs200 class project
*************************************************************************/
#pragma once

#include <functional>
#include "../../MathLibrary/MathLibrary.hpp"
#include "../../Vertex/Vertex.hpp"
#include "../SpriteBatch/SpriteBatch.hpp"
#include "../../Texture/Texture.hpp"

class Particle {
public:
    Vector2<float> position = Vector2<float>(0.0f);
    Vector2<float> velocity = Vector2<float>(0.0f);
    Color color;
    float life = 0.0f;
    float width = 0.0f;
};

inline void defaultParticleUpdate(Particle& particle, float deltaTime) {
    particle.position += particle.velocity * deltaTime;
}

class SpriteParticle {
public:
    SpriteParticle();
    ~SpriteParticle();

    void init(int maxParticles,
        float decayRate,
        GLTexture texture,
        std::function<void(Particle&, float)> updateFunc = defaultParticleUpdate);

    void update(float deltaTime);

    void draw(SpriteBatch* spriteBatch);

    void addParticle(const Vector2<float>& position,
        const Vector2<float>& velocity,
        const Color& color,
        float width);

private:
    int FreeParticleNum();

    std::function<void(Particle&, float)> m_updateFunc;
    float m_decayRate = 0.1f;
    Particle* m_particles = nullptr;
    int m_maxParticles = 0;
    int m_lastFreeParticle = 0;
    GLTexture m_texture;
};
