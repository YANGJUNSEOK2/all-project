
#pragma once
#include <glew.h>

namespace JS_Engine {
    namespace Graphics {
        class IndexBuffer {
        public:

            IndexBuffer(GLuint *p_Data, GLsizei p_Count);

            ~IndexBuffer();
            //Bind Buffer
            void BindBuffer() const;
            //Unbind Buffer
            void UnbindBuffer() const;
            //Calculate Number of Indices
            inline GLuint GetIndexCount() const { return m_IndexCount; }
        private:
            GLuint m_BufferID;
            GLuint m_IndexCount;
        };
    }
}
