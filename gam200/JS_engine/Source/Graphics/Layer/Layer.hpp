#pragma once
#include "../Render/Renderer.hpp"

namespace JS_Engine {
    namespace Graphics {
        class Layer {
        public:

            virtual ~Layer();
            //Add Layer
            virtual void AddLayer(Render *p_Render);
            //Draw Layer
            virtual void DrawLayer();
        protected:
            Renderer            *m_Renderer;
            Shader              *m_Shader;
            MathLibrary::Matrix  m_ProjectionMatrix;
            std::vector<Render*> m_RenderObject;

            Layer(Renderer *p_Renderer, Shader *p_Shader, MathLibrary::Matrix p_ProjectionMatrix);
        };
    }
}