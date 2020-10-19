#pragma once

#include <chrono>

namespace fireworks { namespace utils {

    /// Timer class to keep track of the time.
    class Timer
    {
    private:
        typedef std::chrono::high_resolution_clock HighResolutionClock;
        typedef std::chrono::duration<float, std::milli> milliseconds_type;
        std::chrono::time_point<HighResolutionClock> m_Start;
    public:
        /// Simple Initializer of the timer object that
        Timer()
        {
            reset();
        }

        /// resets the timer to current time 
        void reset()
        {
            m_Start = HighResolutionClock::now();
        }

		/// The completion time in milli seconds since the last frame was renderer.
		/// 
		/// Basically gives the time taken in between rendering two frames in milliseconds
        float deltaTime()
        {
            return std::chrono::duration_cast<milliseconds_type>(HighResolutionClock::now() - m_Start).count() / 1000.0f;
        }
    };
} }
