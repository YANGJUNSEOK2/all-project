#pragma once
#include <deque>
#include "Renderer.hpp"
#include "../Sprite/StaticSprite.hpp"

namespace JS_Engine {
    namespace Graphics {
        class RenderRegular : public Renderer {
        public:
            //Submit Renderer
            void SubmitRenderer(const Render *p_Render) override;
            //Flush Renderer
            void FlushRenderer() override;
        private:
            std::deque<const StaticSprite*> m_RenderQueue;
        };
    }
}