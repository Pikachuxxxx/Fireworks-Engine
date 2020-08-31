#pragma once

#include <iostream>

namespace fireworks { namespace maths {

    struct vec3
    {
        float x, y, z;

        vec3();
        vec3(const float& x, const float& y, const float& z);

        vec3& add(const vec3& other);
        vec3& subtract(const vec3& other);
        vec3& mutiply(const vec3& other);
        vec3& divide(const vec3& other);

        /*
         * friend because we are passing the left and right explicitly and not using
         * this pointer we dont want to pass in the this pointer to the function hence
         * we mark them as non-member friend and still give it access to the private members
         */
        friend vec3& operator+(vec3& left, const vec3& right);
        friend vec3& operator-(vec3& left, const vec3& right);
        friend vec3& operator*(vec3& left, const vec3& right);
        friend vec3& operator/(vec3& left, const vec3& right);

        bool operator==(const vec3& other);
        bool operator!=(const vec3& other);

        vec3& operator+=(const vec3& other);
        vec3& operator-=(const vec3& other);
        vec3& operator*=(const vec3& other);
        vec3& operator/=(const vec3& other);

        friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
    };

} }
