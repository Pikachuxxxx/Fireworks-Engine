#pragma once

#if defined(__GNUC__) || defined(__clang__)
#define DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED __declspec(deprecated)
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED
#endif

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

	DEPRECATED inline double toRadians(float degrees) {
		return (double)degrees * M_PI / 180.0f;
	}

	DEPRECATED inline double toDegrees(float radians) {
		return (double)radians * 180.0f / M_PI;
	}

    template <class T>
    T DEPRECATED inline clamp(T number, T min, T max, T maxX, T minX)
    {
        return (max - min) * ((number - minX) / (maxX - minX)) + min;
    }

    // FIXME: Only works for non-floating types
	 template <class T>
    T DEPRECATED inline getRandomValue(T startRange, T endRange)
    {
        T var = startRange + (T(rand()) / T(RAND_MAX) * (endRange - startRange));
        return var;
    }

	DEPRECATED static maths::vec3 fromGLMVec3(const glm::vec3& v) { return maths::vec3(v.x, v.y, v.z); }
	DEPRECATED static maths::vec4 fromGLMVec4(const glm::vec4& v) { return maths::vec4(v.x, v.y, v.z, v.w); }
    // TODO: Implement this!
	//DEPRECATED//static maths::vec3 fromGLMat3(const glm::vec3& v) { return maths::vec3(v.x, v.y, v.z); }
	//DEPRECATED//static maths::vec3 fromGLMat4(const glm::vec3& v) { return maths::vec3(v.x, v.y, v.z); }

	DEPRECATED static glm::vec3 toGLMVec3(const maths::vec3& v) { return glm::vec3(v.x, v.y, v.z); }
	DEPRECATED static glm::vec4 toGLMVec4(const maths::vec4& v) { return glm::vec4(v.x, v.y, v.z, v.w); }
	// TODO: Implement this!
	//DEPRECATED//static maths::vec3 toGLMat3(const glm::vec3& v) { return maths::vec3(v.x, v.y, v.z); }
	//DEPRECATED//static maths::vec3 toGLMat4(const glm::vec3& v) { return maths::vec3(v.x, v.y, v.z); } 
} }
