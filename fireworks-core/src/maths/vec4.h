#pragma once

#include <iostream>

namespace fireworks { namespace maths {

    struct vec4
    {
        float x, y, z, w;

        vec4();
        vec4(const float& x, const float& y, const float& z, const float& w);

        vec4& add(const vec4& other);
        vec4& subtract(const vec4& other);
        vec4& mutiply(const vec4& other);
        vec4& divide(const vec4& other);

        /*
         * friend because we are passing the left and right explicitly and not using
         * this pointer we dont want to pass in the this pointer to the function hence
         * we mark them as non-member friend and still give it access to the private members
         */
        friend vec4& operator+(vec4& left, const vec4& right);
        friend vec4& operator-(vec4& left, const vec4& right);
        friend vec4& operator*(vec4& left, const vec4& right);
        friend vec4& operator/(vec4& left, const vec4& right);

        bool operator==(const vec4& other);
        bool operator!=(const vec4& other);

        vec4& operator+=(const vec4& other);
        vec4& operator-=(const vec4& other);
        vec4& operator*=(const vec4& other);
        vec4& operator/=(const vec4& other);

        friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
    };

} }
