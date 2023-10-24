#pragma once
#include <Windows.h>

namespace JS_Engine {
    namespace Tools {
        class Timer {
        public:
            Timer() {
                LARGE_INTEGER Frequency;
                QueryPerformanceFrequency(&Frequency);
                m_Frequency = 1.0 / Frequency.QuadPart;
                QueryPerformanceCounter(&m_Start);
            }
            //Reset
            void ResetTimer() {
                QueryPerformanceCounter(&m_Start);
            }
            //Elapsed
            float ElapsedTimer() {
                LARGE_INTEGER CurrentTime;
                QueryPerformanceCounter(&CurrentTime);
                unsigned __int64 TimeCycle = CurrentTime.QuadPart - m_Start.QuadPart;
                return (float)(TimeCycle * m_Frequency);
            }
        private:
            LARGE_INTEGER m_Start;
            double        m_Frequency;
        };
    }
}