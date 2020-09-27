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

        mat4();
        mat4(float diagonal);

        // 4X4 Identity Matrix
        static mat4 identity();

        // Mat 4 to Mat4 multiplication
        mat4& multiply(const mat4& other);
        friend mat4 operator*(mat4 left, const mat4& right);
        mat4& operator*=(const mat4& other);

        // Mat4 and Vec3 multiplicaiton
        vec3 multiply(const vec3& other) const;
        friend vec3 operator*(const mat4& left, const vec3& right);

        // Mat4 and Vec4 multiplicaiton
        vec4 multiply(const vec4& other) const;
        friend vec4 operator*(const mat4& left, const vec4& right);

        // TODO: Add matrix transpose

        // Inverting Matrix
        mat4& invert();

        // Projection Matrices
        static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
        static mat4 perspective(float fov, float aspectRatio, float near , float far);

        // View Transformation Matrices
        static mat4 translation(const vec3& translation);
        static mat4 rotation(float angle, const vec3& axis);
        static mat4 scale(const vec3& scale);

        // Right Shift operator overload to print the matrix to the (character output : cout) or any output stream
        friend std::ostream& operator<<(std::ostream& stream, const mat4& matrix);
    };

} }
