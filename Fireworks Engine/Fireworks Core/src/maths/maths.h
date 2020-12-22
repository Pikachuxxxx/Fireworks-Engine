#pragma once

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

namespace fireworks { namespace maths {

	inline double toRadians(float degrees) {
		return (double)degrees * M_PI / 180.0f;
	}

	inline double toDegrees(float radians) {
		return (double)radians * 180.0f / M_PI;
	}

    template <class T>
    T inline clamp(T number, T min, T max, T maxX, T minX)
    {
        return (max - min) * ((number - minX) / (maxX - minX)) + min;
    }

    // FIXME: Only works for non-floating types
    template <class T>
    T inline getRandomValue(T min, T max)
    {
        return (T(min) + (std::rand() % (max - min + 1)));
    }


} }
