#pragma once

#include <chrono>

namespace fireworks { namespace utils {

    class Timer
    {
    private:
        typedef std::chrono::high_resolution_clock HighResolutionClock;
        typedef std::chrono::duration<float, std::milli> milliseconds_type;
        std::chrono::time_point<HighResolutionClock> m_Start;
    public:
        Timer()
        {
            reset();
        }

        void reset()
        {
            m_Start = HighResolutionClock::now();
        }

        float elapsed()
        {
            return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - m_Start).count() / 1000.0f;
        }
    };
} }
