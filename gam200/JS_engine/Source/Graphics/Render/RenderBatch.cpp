#include "RenderBatch.hpp"

namespace JS_Engine {
    namespace Graphics {
        using namespace MathLibrary;

        RenderBatch::RenderBatch() {
            InitializeBatch();
        }

        RenderBatch::~RenderBatch() {
            delete m_IBO;
            glDeleteBuffers(1, &m_VBO);
        }

        void RenderBatch::SubmitRenderer(const Render *p_Render) {
            const Vector3 &Position = p_Render->GetPosition();
            const Vector2 &Size = p_Render->GetSize();
            const Vector4 &Color = p_Render->GetColor();

            int Red = Color.XComponent * 255.0f;
            int Green = Color.YComponent * 255.0f;
            int Blue = Color.ZComponent * 255.0f;
            int Alpha = Color.WComponent * 255.0f;

            unsigned int ColorData = Alpha << 24 | Blue << 16 | Green << 8 | Red;

            m_Buffer->Vertex = *m_StackBack * Position;
            m_Buffer->Color = ColorData;
            m_Buffer++;
            m_Buffer->Vertex = *m_StackBack * Vector3(Position.XComponent, Position.YComponent + Size.YComponent, Position.ZComponent);
            m_Buffer->Color = ColorData;
            m_Buffer++;
            m_Buffer->Vertex = *m_StackBack * Vector3(Position.XComponent + Size.XComponent, Position.YComponent + Size.YComponent, Position.ZComponent);
            m_Buffer->Color = ColorData;
            m_Buffer++;
            m_Buffer->Vertex = *m_StackBack * Vector3(Position.XComponent + Size.XComponent, Position.YComponent, Position.ZComponent);
            m_Buffer->Color = ColorData;
            m_Buffer++;

            m_IndexCount += 6;
        }

        void RenderBatch::FlushRenderer() {
            glBindVertexArray(m_VAO);
            m_IBO->BindBuffer();
            glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);
            m_IBO->UnbindBuffer();
            glBindVertexArray(0);

            m_IndexCount = 0;
        }

        void RenderBatch::BeginRenderer() {
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        }

        void RenderBatch::EndRenderer() {
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void RenderBatch::InitializeBatch() {
            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);
            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, BufferSizeM, NULL, GL_DYNAMIC_DRAW);
            glVertexAttribPointer(VertexIndexM, 3, GL_FLOAT, GL_FALSE, VertexSizeM, (const GLvoid*)0);
            glVertexAttribPointer(ColorIndexM, 4, GL_UNSIGNED_BYTE, GL_TRUE, VertexSizeM, (const GLvoid*)(offsetof(VertexData, VertexData::Color)));
            glEnableVertexAttribArray(VertexIndexM);
            glEnableVertexAttribArray(ColorIndexM);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            GLuint *Indices = new GLuint[IndexSizeM];
            int Offset = 0;
            for (int i = 0; i < IndexSizeM; i += 6) {
                Indices[i + 0] = Offset + 0;
                Indices[i + 1] = Offset + 1;
                Indices[i + 2] = Offset + 2;
                Indices[i + 3] = Offset + 2;
                Indices[i + 4] = Offset + 3;
                Indices[i + 5] = Offset + 0;
                Offset += 4;
            }
            m_IBO = new IndexBuffer(Indices, IndexSizeM);
            glBindVertexArray(0);
        }
    }
}