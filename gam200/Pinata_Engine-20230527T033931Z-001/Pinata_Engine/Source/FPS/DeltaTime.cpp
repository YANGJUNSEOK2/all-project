#include "DeltaTime.hpp"

DeltaTime::DeltaTime() noexcept : timeStamp(clock_t::now())
{
}

void DeltaTime::ResetTimeStamp() noexcept
{
    timeStamp = clock_t::now();
}

float DeltaTime::GetElapsedSeconds() const noexcept
{
    return std::chrono::duration_cast<second_t>(clock_t::now() - timeStamp).count();
}