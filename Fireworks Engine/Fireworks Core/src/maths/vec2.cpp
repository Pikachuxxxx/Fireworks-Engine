#include "vec2.h"


namespace fireworks { namespace maths {

    vec2::vec2()
    {
        x = 0.0f;
        y = 0.0f;
    }

    vec2::vec2(const float& x, const float& y)
    {
        this->x = x;
        this->y = y;
    }

	vec2& vec2::add(const vec2& other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    vec2& vec2::subtract(const vec2& other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }
    vec2& vec2::mutiply(const vec2& other)
    {
        x *= other.x;
        y *= other.y;

        return *this;
    }
    vec2& vec2::divide(const vec2& other)
    {
        x /= other.x;
        y /= other.y;

        return *this;
    }

    float vec2::magSquared()
    {
        return (x * x) + (y * y);
    }

    vec2 operator+(vec2 left, const vec2& right)
    {
        return left.add(right);
    }

    vec2 operator-(vec2 left, const vec2& right)
    {
        return left.subtract(right);
    }

    vec2 operator*(vec2 left, const vec2& right)
    {
        return left.mutiply(right);
    }

    vec2 operator/(vec2 left, const vec2& right)
    {
        return left.divide(right);
    }

    vec2 operator*(vec2 left, const float& right)
    {
        return vec2(left.x * right, left.y * right);
    }

    bool vec2::operator==(const vec2& other)
    {
        return x == other.x && y == other.y;
    }

    bool vec2::operator!=(const vec2& other)
    {
        return !(*this == other);
    }

    vec2& vec2::operator+=(const vec2& other)
    {
        return add(other);
    }

    vec2& vec2::operator-=(const vec2& other)
    {
        return subtract(other);
    }

    vec2& vec2::operator*=(const vec2& other)
    {
        return mutiply(other);
    }

    vec2& vec2::operator*=(const float& other)
    {
        return mutiply(vec2(other, other));
    }

    vec2& vec2::operator/=(const vec2& other)
    {
        return divide(other);
    }

    std::ostream& operator<<(std::ostream& stream, const vec2& vector)
    {
        stream << "vec2: (" << vector.x << ", " << vector.y << ")";
        return stream;
    }

} }
