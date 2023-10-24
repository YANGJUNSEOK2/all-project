
#include "IndexBuffer.hpp"

namespace JS_Engine {
    namespace Graphics {

        IndexBuffer::IndexBuffer(GLuint *p_Data, GLsizei p_Count) : m_IndexCount(p_Count) {
            glGenBuffers(1, &m_BufferID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * p_Count, p_Data, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        IndexBuffer::~IndexBuffer() {
            glDeleteBuffers(1, &m_BufferID);
        }

        void IndexBuffer::BindBuffer() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
        }

        void IndexBuffer::UnbindBuffer() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }
}