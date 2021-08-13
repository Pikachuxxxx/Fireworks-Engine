 #pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "maths.h"

namespace fireworks { namespace maths {

    struct mat4
    {
        union
        {
            float elements[4 * 4];
            vec4 columns[4];
        };

        DEPRECATED mat4();
        DEPRECATED mat4(float diagonal);

        // 4X4 Identity Matrix
        DEPRECATED static mat4 identity();

        // Mat 4 to Mat4 multiplication
        DEPRECATED mat4& multiply(const mat4& other);
        DEPRECATED friend mat4 operator*(mat4 left, const mat4& right);
        DEPRECATED mat4& operator*=(const mat4& other);

        // Mat4 and Vec3 multiplication
        DEPRECATED vec3 multiply(const vec3& other) const;
        DEPRECATED friend vec3 operator*(const mat4& left, const vec3& right);

        // Mat4 and Vec4 multiplication
        DEPRECATED vec4 multiply(const vec4& other) const;
        DEPRECATED friend vec4 operator*(const mat4& left, const vec4& right);

        // TODO: Add matrix transpose

        // Inverting Matrix
        DEPRECATED mat4& invert();

        // Projection Matrices
		DEPRECATED static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
		DEPRECATED static mat4 perspective(float fov, float aspectRatio, float near, float far);

        // View Transformation Matrices
        DEPRECATED static mat4 translation(const vec3& translation);
        DEPRECATED static mat4 rotation(float angle, const vec3& axis);
        DEPRECATED static mat4 scale(const vec3& scale);

        // LookAt Matrix
        DEPRECATED static mat4 lookAt(const vec3& eye, const vec3& target, const vec3& worldUp = vec3(0, 1, 0));

        // Right Shift operator overload to print the matrix to the (character output : cout) or any output stream
        DEPRECATED friend std::ostream& operator<<(std::ostream& stream, const mat4& matrix);
    };

} }
