#include "Layer.hpp"

namespace JS_Engine {
    namespace Graphics {

        Layer::~Layer() {
            delete m_Shader;
            delete m_Renderer;
            for (int i = 0; i < m_RenderObject.size(); i++) {
                delete m_RenderObject[i];
            }
        }

        void Layer::AddLayer(Render *p_Render) {
            m_RenderObject.push_back(p_Render);
        }

        void Layer::DrawLayer() {
            m_Shader->ShaderEnable();
            m_Renderer->BeginRenderer();
            for (const Render *p_RenderObject : m_RenderObject) {
                m_Renderer->SubmitRenderer(p_RenderObject);
            }
            m_Renderer->EndRenderer();
            m_Renderer->FlushRenderer();
        }

        Layer::Layer(Renderer *p_Renderer, Shader *p_Shader, MathLibrary::Matrix p_ProjectionMatrix)
            : m_Renderer(p_Renderer), m_Shader(p_Shader), m_ProjectionMatrix(p_ProjectionMatrix) {
            m_Shader->ShaderEnable();
            m_Shader->SetUniformMatrix("ProjectionMatrix", m_ProjectionMatrix);
            m_Shader->ShaderDisable();
        }
    }
}