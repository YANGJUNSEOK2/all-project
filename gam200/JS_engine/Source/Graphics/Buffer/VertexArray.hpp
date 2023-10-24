#pragma once
#include <vector>
#include <glew.h>
#include "VertexBuffer.hpp"

namespace JS_Engine {
    namespace Graphics {
        class VertexArray {
        public:

            VertexArray();

            ~VertexArray();
            //Add Vertex Buffer
            void AddBuffer(VertexBuffer *p_Buffer, GLuint p_Index);
            //Bind Buffer
            void BindBuffer() const;
            //Unbind Buffer
            void UnbindBuffer() const;
        private:
            GLuint m_ArrayID;
            std::vector<VertexBuffer*>m_Buffer;
        };
    }
}