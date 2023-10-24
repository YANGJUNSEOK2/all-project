#include "RenderRegular.hpp"

namespace JS_Engine {
    namespace Graphics {
        //Submit Renderer
        void RenderRegular::SubmitRenderer(const Render *p_Render) {
            m_RenderQueue.push_back((StaticSprite*)p_Render);
        }
        //Flush Renderer
        void RenderRegular::FlushRenderer() {
            while (!m_RenderQueue.empty()) {
                const StaticSprite *SpriteData = m_RenderQueue.front();
                SpriteData->GetVAO()->BindBuffer();
                SpriteData->GetIBO()->BindBuffer();
                SpriteData->GetShader().SetUniformMatrix("ModelMatrix", MathLibrary::Matrix::Translate(SpriteData->GetPosition()));
                glDrawElements(GL_TRIANGLES, SpriteData->GetIBO()->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
                SpriteData->GetIBO()->UnbindBuffer();
                SpriteData->GetVAO()->UnbindBuffer();
                m_RenderQueue.pop_front();
            }
        }
    }
}