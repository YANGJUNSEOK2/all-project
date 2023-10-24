/************************************************************************
*	File name : SpriteGame.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION
*************************************************************************/
#pragma once
#include <glew.h>
#include "../Vertex/Vertex.hpp"
#include <cstddef>
#include "../Texture/GLTexture.hpp"
#include <string>


class SpriteGame
{
public:
    SpriteGame();
    ~SpriteGame();

    // p_X p_Y POINT p_Width p_Height SIZE
    void Init(float p_X, float p_Y, float p_Width, float p_Height, std::string texturePath);


    void Draw();

private:
    float m_X;
    float m_Y;
    float m_Width;
    float m_Height;
    GLuint m_VBOId;
    GLTexture m_Texture;
};
