#pragma once
#include "../Render/Render.hpp"

namespace JS_Engine {
    namespace Graphics {
        class StaticSprite : public Render {
        public:
            inline const VertexArray *GetVAO()      const { return m_VertexArray; }
            inline const IndexBuffer *GetIBO()	    const { return m_IndexBuffer; }
            inline		 Shader      &GetShader()	const { return m_Shader; }

            StaticSprite(float p_XComponent, float p_YComponent, float p_Width, float p_Height, const MathLibrary::Vector4 &p_Color, Shader &p_Shader);

            ~StaticSprite();
        private:
            VertexArray *m_VertexArray;
            IndexBuffer *m_IndexBuffer;
            Shader		&m_Shader;
        };
    }
}