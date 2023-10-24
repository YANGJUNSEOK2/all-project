#include "VertexBuffer.hpp"

namespace JS_Engine {
    namespace Graphics {

        VertexBuffer::VertexBuffer(GLfloat *p_Data, GLsizei p_Count, GLuint p_ElementCount) : m_ElementCount(p_ElementCount) {
            glGenBuffers(1, &m_BufferID);
            glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * p_Count, p_Data, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        VertexBuffer::~VertexBuffer() {
            glDeleteBuffers(1, &m_BufferID);
        }

        void VertexBuffer::BindBuffer() const {
            glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
        }

        void VertexBuffer::UnbindBuffer() const {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}