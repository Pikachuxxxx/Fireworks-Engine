#pragma once

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

namespace fireworks { namespace maths {

	inline float toRadians(float degrees) {
		return degrees * M_PI / 180.0f;
	}

    template <class T>
    T inline clamp(T number, T min, T max, T maxX, T minX)
    {
        return (max - min) * ((number - minX) / (maxX - minX)) + min;
    }

    template <class T>
    T getRandomValue(T min, T max)
    {
        return (min + (std::rand() % (max - min + 1)));
    }


} }
