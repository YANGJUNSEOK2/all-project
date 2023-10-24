/************************************************************************
*	File name : SpriteGame.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION 2019 Fall Semester  cs200 class project
*************************************************************************/
#include"SpriteGame.hpp"

#include "../Shader/glCheck/glCheck.hpp"
#include "../Texture/Texture.hpp"

SpriteGame::SpriteGame()
{
    m_VBOId = 0;
}

SpriteGame::~SpriteGame()
{
    if (m_VBOId != 0)
    {
        glCheck(glDeleteBuffers(1, &m_VBOId));
    }
}
// p_X p_Y POINT p_Width p_Height SIZE
void SpriteGame::Init(float p_X, float p_Y, float p_Width, float p_Height, std::string p_TexturePath)
{
    m_Texture = Texture::GetTexture(p_TexturePath);

    if (m_VBOId == 0)
    {
        glCheck(glGenBuffers(1, &m_VBOId));
    }

    Vertex p_VertexData[6];

    p_VertexData[0].setPosition(p_X + p_Width, p_Y + p_Height);
    p_VertexData[0].setUV(1.0f, 1.0f);

    m_topLeftPoint[0] = p_VertexData[0].getPosition();
    m_topLeftUV[0] = p_VertexData[0].getUV();

    p_VertexData[1].setPosition(p_X, p_Y + p_Height);
    p_VertexData[1].setUV(0.0f, 1.0f);

    m_bottomLeftPoint[1] = p_VertexData[1].getPosition();
    m_bottomLeftUV[1] = p_VertexData[1].getUV();

    p_VertexData[2].setPosition(p_X, p_Y);
    p_VertexData[2].setUV(0.0f, 0.0f);

    m_bottomRightPoint[2] = p_VertexData[2].getPosition();
    m_bottomRightUV[2] = p_VertexData[2].getUV();

    p_VertexData[3].setPosition(p_X, p_Y);
    p_VertexData[3].setUV(0.0f, 0.0f);

    m_bottomRightPoint[3] = p_VertexData[3].getPosition();
    m_bottomRightUV[3] = p_VertexData[3].getUV();

    p_VertexData[4].setPosition(p_X + p_Width, p_Y);
    p_VertexData[4].setUV(1.0f, 0.0f);

    m_topRightPoint[4] = p_VertexData[4].getPosition();
    m_topRightUV[4] = p_VertexData[4] .getUV();

    p_VertexData[5].setPosition(p_X + p_Width, p_Y + p_Height);
    p_VertexData[5].setUV(1.0f, 1.0f);

    m_bottomRightPoint[5] = p_VertexData[5].getPosition();
    m_bottomRightUV[5] = p_VertexData[5].getUV();

    for (int i = 0; i < 6; i++)
    {
        p_VertexData[i].setColor(255, 255, 255, 255);
    }

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_VBOId));
    glCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(p_VertexData), p_VertexData, GL_STATIC_DRAW));

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void SpriteGame::Draw()
{
    glCheck(glBindTexture(GL_TEXTURE_2D, m_Texture.id));

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_VBOId));

    glCheck(glEnableVertexAttribArray(0));
    glCheck(glEnableVertexAttribArray(1));
    glCheck(glEnableVertexAttribArray(2));

    //This is position attribute pointer
    glCheck(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)));
    //This is color attribute pointer
    glCheck(glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)));
    //This is uv attribute pointer
    glCheck(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv)));

    glCheck(glDrawArrays(GL_TRIANGLES, 0, 6));

    glCheck(glDisableVertexAttribArray(0));
    glCheck(glDisableVertexAttribArray(1));
    glCheck(glDisableVertexAttribArray(2));

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
