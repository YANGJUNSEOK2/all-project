#include"Sprite.hpp"
#include "Vertex/Vertex.hpp"
#include <cstddef>

namespace JS_Engine {
    namespace MainSystem {
        Sprite::Sprite()
        {
            m_VBOId = 0;
        }

        Sprite::~Sprite()
        {
            if(m_VBOId != 0)
            {
                glDeleteBuffers(1, &m_VBOId);
            }
        }

        void Sprite::Init(float p_X, float p_Y, float p_Width, float p_Height)
        {
            m_X = p_X;
            m_Y = p_Y;
            m_Width = p_Width;
            m_Height = p_Height;

            if(m_VBOId == 0)
            {
                glGenBuffers(1, &m_VBOId);
            }

            Vertex p_VertexData[6];

            p_VertexData[0].setPosition(p_X + p_Width, p_Y + p_Height);
            p_VertexData[0].setUV(1.0f, 1.0f);

            p_VertexData[1].setPosition(p_X, p_Y + p_Height);
            p_VertexData[1].setUV(0.0f, 1.0f);

            p_VertexData[2].setPosition(p_X, p_Y);
            p_VertexData[2].setUV(0.0f, 0.0f);

            p_VertexData[3].setPosition(p_X, p_Y);
            p_VertexData[3].setUV(0.0f, 0.0f);

            p_VertexData[4].setPosition(p_X + p_Width, p_Y);
            p_VertexData[4].setUV(1.0f, 0.0f);

            p_VertexData[5].setPosition(p_X + p_Width, p_Y + p_Height);
            p_VertexData[5].setUV(1.0f, 1.0f);

            for (int i = 0; i < 6; i++)
            {
                p_VertexData[4].setColor(255, 0, 255, 255);
            }

            p_VertexData[1].setColor(0, 0, 255, 255);

            p_VertexData[4].setColor(0, 255, 0, 255);

            glBindBuffer(GL_ARRAY_BUFFER, m_VBOId);
            glBufferData(GL_ARRAY_BUFFER, sizeof(p_VertexData), p_VertexData,GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void Sprite::Draw()
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_VBOId);

            glEnableVertexAttribArray(0);

            //This is position attribute pointer
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,position));
            //This is color attribute pointer
            glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
            //This is uv attribute pointer
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

            glDrawArrays(GL_TRIANGLES, 0, 6);

            glDisableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}