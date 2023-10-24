/************************************************************************
*	File name : SpriteGame.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION 2019 Fall Semester cs200 class project
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
    //void Init(float p_X, float p_Y, float p_Width, float p_Height);

    void Draw();

    void setTopLeftPoint(Vector2<float> *point) { m_topLeftPoint = point; }
    void setBottomLeftPoint(Vector2<float> *point) { m_bottomLeftPoint = point; }
    void setTopRightPoint(Vector2<float> *point) { m_topRightPoint = point; }
    void setBottomRightPoint(Vector2<float> *point) { m_bottomRightPoint = point; }

    void setTopLeftUV(Vector2<float> *point) { m_topLeftUV = point; }
    void setBottomLeftUV(Vector2<float> *point) { m_bottomLeftUV = point; }
    void setTopRightUV(Vector2<float> *point) { m_topRightUV = point; }
    void setBottomRightUV(Vector2<float> *point) { m_bottomRightUV = point; }

    GLuint getVBO() { return m_VBOId; }

private:
    float m_X;
    float m_Y;
    float m_Width;
    float m_Height;
    GLuint m_VBOId;
    GLTexture m_Texture;


    Vector2<float> *m_topLeftPoint;
    Vector2<float> *m_bottomLeftPoint;
    Vector2<float> *m_topRightPoint;
    Vector2<float> *m_bottomRightPoint;

    Vector2<float> *m_topLeftUV;
    Vector2<float> *m_bottomLeftUV;
    Vector2<float> *m_topRightUV;
    Vector2<float> *m_bottomRightUV;
};
