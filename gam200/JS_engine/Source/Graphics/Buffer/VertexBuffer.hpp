#pragma once
#include <glew.h>

namespace JS_Engine {
    namespace Graphics {
        class VertexBuffer {
        public:

            VertexBuffer(GLfloat *p_Data, GLsizei p_Count, GLuint p_ElementCount);

            ~VertexBuffer();
            //Bind Buffer
            void BindBuffer() const;
            //Unbind Buffer
            void UnbindBuffer() const;
            //Calculate Number of Elements
            inline GLuint GetElementCount() const { return m_ElementCount; }
        private:
            GLuint m_BufferID;
            GLuint m_ElementCount;
        };
    }
}