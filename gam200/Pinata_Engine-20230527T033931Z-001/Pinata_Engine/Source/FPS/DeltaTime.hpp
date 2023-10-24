#pragma once
#include <chrono>

class DeltaTime
{
public:
    DeltaTime() noexcept;

    void ResetTimeStamp() noexcept;

    float GetElapsedSeconds() const noexcept;
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<float, std::ratio<1>>;

    std::chrono::time_point<clock_t> timeStamp;
};