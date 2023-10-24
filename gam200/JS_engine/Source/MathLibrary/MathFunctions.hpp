#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace JS_Engine {
    namespace MathLibrary {
        //Convert Degree to Radian
        inline float DegreeToRadian(float p_Degree) {
            return static_cast<float>(p_Degree * (M_PI / 180.0f));
        }
    }
}