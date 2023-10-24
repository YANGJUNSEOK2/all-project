
#pragma once

#include <vector>
#include <../../Source/MathLibrary/MathLibrary.hpp>

namespace JS_Engine {
    namespace LevelSystem {
    class LevelState
    {
    public:
        //Level Initialize
        virtual void Initialize() = 0;
        //Level Update
        virtual void Update() = 0;
        //Level Close
        virtual void Close() = 0;

        virtual ~LevelState();
    };
}}
