
#include "VertexArray.hpp"

namespace JS_Engine {
    namespace Graphics {

        VertexArray::VertexArray() {
            glGenVertexArrays(1, &m_ArrayID);
        }

        VertexArray::~VertexArray() {
            for (int i = 0; i < m_Buffer.size(); i++) {
                delete m_Buffer[i];
            }
            glDeleteVertexArrays(1, &m_ArrayID);
        }

        void VertexArray::AddBuffer(VertexBuffer *p_Buffer, GLuint p_Index) {
            BindBuffer();
            p_Buffer->BindBuffer();
            glEnableVertexAttribArray(p_Index);
            glVertexAttribPointer(p_Index, p_Buffer->GetElementCount(), GL_FLOAT, GL_FALSE, 0, 0);
            p_Buffer->UnbindBuffer();
            UnbindBuffer();
        }

        void VertexArray::BindBuffer() const {
            glBindVertexArray(m_ArrayID);
        }

        void VertexArray::UnbindBuffer() const {
            glBindVertexArray(0);
        }
    }
}