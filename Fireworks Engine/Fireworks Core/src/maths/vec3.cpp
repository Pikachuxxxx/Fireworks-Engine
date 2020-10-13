#include "vec3.h"


namespace fireworks { namespace maths {

    vec3::vec3()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    vec3::vec3(const float& x, const float& y, const float& z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

	vec3 vec3::crossProduct(const vec3& a, const vec3& b)
	{
        return vec3(a.y * b.z - a.z * b.y,
			        a.x * b.z - a.z * b.x,
			        a.x * b.y - a.y * b.x);
	}

	vec3 vec3::normalize(const vec3& v)
	{
		float length_of_v = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
		return vec3(v.x / length_of_v, v.y / length_of_v, v.z / length_of_v);
	}

	vec3& vec3::add(const vec3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    vec3& vec3::subtract(const vec3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;

        return *this;
    }
    vec3& vec3::mutiply(const vec3& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;

        return *this;
    }
    vec3& vec3::divide(const vec3& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;

        return *this;
    }

    vec3 operator+(vec3 left, const vec3& right)
    {
        return left.add(right);
    }

    vec3 operator-(vec3 left, const vec3& right)
    {
        return left.subtract(right);
    }

    vec3 operator*(vec3 left, const vec3& right)
    {
        return left.mutiply(right);
    }

    vec3 operator/(vec3 left, const vec3& right)
    {
        return left.divide(right);
    }

    bool vec3::operator==(const vec3& other)
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool vec3::operator!=(const vec3& other)
    {
        return !(*this == other);
    }

    vec3& vec3::operator+=(const vec3& other)
    {
        return add(other);
    }

    vec3& vec3::operator-=(const vec3& other)
    {
        return subtract(other);
    }

    vec3& vec3::operator*=(const vec3& other)
    {
        return mutiply(other);
    }

    vec3& vec3::operator/=(const vec3& other)
    {
        return divide(other);
    }

    std::ostream& operator<<(std::ostream& stream, const vec3& vector)
    {
        stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
        return stream;
    }

} }
