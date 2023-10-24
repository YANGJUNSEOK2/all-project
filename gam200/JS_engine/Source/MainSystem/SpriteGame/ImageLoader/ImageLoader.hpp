#pragma once
#include "../GLTexture/GLTexture.hpp"
#include <string>

namespace JS_Engine {
    namespace MainSystem {
        class ImageLoader
        {
        public:
            static GLTexture loadPNG(std::string filePath);
        };

    }
}
