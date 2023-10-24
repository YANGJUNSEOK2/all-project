#pragma once
#include "Renderer.hpp"
#include "../Buffer/IndexBuffer.hpp"

namespace JS_Engine {
    namespace Graphics {
#define VertexIndexM		0
#define ColorIndexM		1
#define MaximumSpriteM	60000
#define VertexSizeM		sizeof(VertexData)
#define SpriteSizeM		VertexSizeM * 4
#define BufferSizeM		MaximumSpriteM * SpriteSizeM
#define IndexSizeM		MaximumSpriteM * 6

        class RenderBatch : public Renderer {
        public:

            RenderBatch();

            ~RenderBatch();
            //Submit Renderer
            void SubmitRenderer(const Render *p_Render) override;
            //Flush Renderer
            void FlushRenderer() override;
            //Begin Renderer
            void BeginRenderer() override;
            //End Renderer
            void EndRenderer() override;
        private:
            GLuint		 m_VAO;
            GLuint		 m_VBO;
            IndexBuffer *m_IBO;
            GLsizei		 m_IndexCount;
            VertexData	*m_Buffer;
            //Initialize Batch Renderer
            void InitializeBatch();
        };
    }
}