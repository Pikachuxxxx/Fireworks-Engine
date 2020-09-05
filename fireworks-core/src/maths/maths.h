#pragma once

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"


namespace fireworks { namespace maths {

	inline float toRadians(float degrees) {
		return degrees * M_PI / 180.0f;
	}

    inline float clampFloat(float number, float min, float max, float maxX, float minX)
    {
        return (max - min) * ((number - minX) / (maxX - minX)) + min;

    }

    // template<typename T>
    // int clamp(int& number, int rangeA, int rangeB ) {}
    //
    // template<>
    // float clamp<float>(float& number, float rangeA, float rangeB )
    // {
    //     m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
    //     m_stride += VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT) * count;
    // }
    //
    // template<>
    // double clamp<double>(double& number, double rangeA, double rangeB )
    // {
    //     m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    //     m_stride += VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
    // }

} }
