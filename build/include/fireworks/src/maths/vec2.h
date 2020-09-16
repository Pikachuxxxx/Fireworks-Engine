#pragma once

#include <iostream>

namespace fireworks { namespace maths {

    struct vec2
    {
        float x, y;

        vec2();
        vec2(const float& x, const float& y);

        vec2& add(const vec2& other);
        vec2& subtract(const vec2& other);
        vec2& mutiply(const vec2& other);
        vec2& divide(const vec2& other);

        /*
         * friend because we are passing the left and right explicitly and not using
         * this pointer we dont want to pass in the this pointer to the function hence
         * we mark them as non-member friend and still give it access to the private members
         */
        friend vec2 operator+(vec2 left, const vec2& right);
        friend vec2 operator-(vec2 left, const vec2& right);
        friend vec2 operator*(vec2 left, const vec2& right);
        friend vec2 operator/(vec2 left, const vec2& right);

        bool operator==(const vec2& other);
        bool operator!=(const vec2& other);

        vec2& operator+=(const vec2& other);
        vec2& operator-=(const vec2& other);
        vec2& operator*=(const vec2& other);
        vec2& operator/=(const vec2& other);

        friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
    };

} }
