#pragma once
#include "Layer.hpp"
#include "../Render/RenderBatch.hpp"

namespace JS_Engine {
    namespace Graphics {
        class TileLayer : public Layer {
        public:

            TileLayer(Shader *p_Shader);

            ~TileLayer();
        };
    }
}