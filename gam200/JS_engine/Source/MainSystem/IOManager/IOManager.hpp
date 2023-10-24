#pragma once
#include <vector>

namespace JS_Engine {
    namespace MainSystem {
        class IOManager
        {
        public:
            static bool readFileToBuffer(std::string p_FilePath, std::vector<unsigned char>& p_Buffer);
        };
    }
}
