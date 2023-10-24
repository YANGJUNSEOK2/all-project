#include "TileLayer.hpp"

namespace JS_Engine {
    namespace Graphics {

        TileLayer::TileLayer(Shader *p_Shader)
            : Layer(new RenderBatch(), p_Shader, MathLibrary::Matrix::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f)) {
        }

        TileLayer::~TileLayer() { }
    }
}