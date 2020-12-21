 #include "mat4.h"

namespace fireworks { namespace maths {

    mat4::mat4()
    {
        for(int i = 0; i < 4 * 4; i++)
            elements[i] = 0.0f;
    }

    mat4::mat4(float diagonal)
    {
        for(int i = 0; i < 4 * 4; i++)
            elements[i] = 0.0f;

        elements[0 + 0 * 4] = diagonal;
        elements[1 + 1 * 4] = diagonal;
        elements[2 + 2 * 4] = diagonal;
        elements[3 + 3 * 4] = diagonal;
    }

    mat4 mat4::identity()
    {
         return mat4(1.0f);
    }

    mat4& mat4::multiply(const mat4& other)
    {
        float data[16];
        for(int y = 0; y < 4; y++)
        {
            for(int x = 0; x < 4; x++)
            {
                float sum = 0.0f;
                for(int e = 0; e < 4; e++)
                {
                    sum += elements[x + e * 4] * other.elements[e + y * 4];
                }
                data[x + y * 4] = sum;
            }
        }
        memcpy(elements, data, 16 * 4);

        return *this;
    }

    mat4 operator*(mat4 left, const mat4& right)
    {
        return left.multiply(right);
    }

    mat4& mat4::operator*=(const mat4& other)
    {
        return multiply(other);
    }

    vec3 mat4::multiply(const vec3& other) const
    {
        return vec3{
            columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
            columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
            columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z
        };
    }

    vec4 mat4::multiply(const vec4& other) const
    {
        return vec4{
            columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.x + columns[3].x * other.w,
            columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
            columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
            columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w,
        };
    }

    vec3 operator*(const mat4& left, const vec3& right)
    {
        return left.multiply(right);
    }

    vec4 operator*(const mat4& left, const vec4& right)
    {
        return left.multiply(right);
    }

    mat4& mat4::invert()
    {
        double temp[16];

        temp[0] =   elements[5]  * elements[10] * elements[15] -
                    elements[5]  * elements[11] * elements[14] -
                    elements[9]  * elements[6]  * elements[15] +
                    elements[9]  * elements[7]  * elements[14] +
                    elements[13] * elements[6]  * elements[11] -
                    elements[13] * elements[7]  * elements[10];

        temp[4] =  -elements[4]  * elements[10] * elements[15] +
                    elements[4]  * elements[11] * elements[14] +
                    elements[8]  * elements[6]  * elements[15] -
                    elements[8]  * elements[7]  * elements[14] -
                    elements[12] * elements[6]  * elements[11] +
                    elements[12] * elements[7]  * elements[10];

        temp[8] =   elements[4]  * elements[9] * elements[15] -
                    elements[4]  * elements[11] * elements[13] -
                    elements[8]  * elements[5] * elements[15] +
                    elements[8]  * elements[7] * elements[13] +
                    elements[12] * elements[5] * elements[11] -
                    elements[12] * elements[7] * elements[9];

        temp[12] = -elements[4]  * elements[9] * elements[14] +
                    elements[4]  * elements[10] * elements[13] +
                    elements[8]  * elements[5] * elements[14] -
                    elements[8]  * elements[6] * elements[13] -
                    elements[12] * elements[5] * elements[10] +
                    elements[12] * elements[6] * elements[9];

        temp[1] =   -elements[1] * elements[10] * elements[15] +
                    elements[1]  * elements[11] * elements[14] +
                    elements[9]  * elements[2] * elements[15] -
                    elements[9]  * elements[3] * elements[14] -
                    elements[13] * elements[2] * elements[11] +
                    elements[13] * elements[3] * elements[10];

        temp[5] =   elements[0]  * elements[10] * elements[15] -
                    elements[0]  * elements[11] * elements[14] -
                    elements[8]  * elements[2] * elements[15] +
                    elements[8]  * elements[3] * elements[14] +
                    elements[12] * elements[2] * elements[11] -
                    elements[12] * elements[3] * elements[10];

        temp[9] =   -elements[0] * elements[9] * elements[15] +
                    elements[0]  * elements[11] * elements[13] +
                    elements[8]  * elements[1] * elements[15] -
                    elements[8]  * elements[3] * elements[13] -
                    elements[12] * elements[1] * elements[11] +
                    elements[12] * elements[3] * elements[9];

        temp[13] =  elements[0]  * elements[9] * elements[14] -
                    elements[0]  * elements[10] * elements[13] -
                    elements[8]  * elements[1] * elements[14] +
                    elements[8]  * elements[2] * elements[13] +
                    elements[12] * elements[1] * elements[10] -
                    elements[12] * elements[2] * elements[9];

        temp[2] =   elements[1]  * elements[6] * elements[15] -
                    elements[1]  * elements[7] * elements[14] -
                    elements[5]  * elements[2] * elements[15] +
                    elements[5]  * elements[3] * elements[14] +
                    elements[13] * elements[2] * elements[7] -
                    elements[13] * elements[3] * elements[6];

        temp[6] =  -elements[0]  * elements[6] * elements[15] +
                    elements[0]  * elements[7] * elements[14] +
                    elements[4]  * elements[2] * elements[15] -
                    elements[4]  * elements[3] * elements[14] -
                    elements[12] * elements[2] * elements[7] +
                    elements[12] * elements[3] * elements[6];

        temp[10] =  elements[0]  * elements[5] * elements[15] -
                    elements[0]  * elements[7] * elements[13] -
                    elements[4]  * elements[1] * elements[15] +
                    elements[4]  * elements[3] * elements[13] +
                    elements[12] * elements[1] * elements[7] -
                    elements[12] * elements[3] * elements[5];

        temp[14] = -elements[0]  * elements[5] * elements[14] +
                    elements[0]  * elements[6] * elements[13] +
                    elements[4]  * elements[1] * elements[14] -
                    elements[4]  * elements[2] * elements[13] -
                    elements[12] * elements[1] * elements[6] +
                    elements[12] * elements[2] * elements[5];

        temp[3] =  -elements[1] * elements[6] * elements[11] +
                    elements[1] * elements[7] * elements[10] +
                    elements[5] * elements[2] * elements[11] -
                    elements[5] * elements[3] * elements[10] -
                    elements[9] * elements[2] * elements[7] +
                    elements[9] * elements[3] * elements[6];

        temp[7] =   elements[0] * elements[6] * elements[11] -
                    elements[0] * elements[7] * elements[10] -
                    elements[4] * elements[2] * elements[11] +
                    elements[4] * elements[3] * elements[10] +
                    elements[8] * elements[2] * elements[7] -
                    elements[8] * elements[3] * elements[6];

        temp[11] = -elements[0] * elements[5] * elements[11] +
                    elements[0] * elements[7] * elements[9] +
                    elements[4] * elements[1] * elements[11] -
                    elements[4] * elements[3] * elements[9] -
                    elements[8] * elements[1] * elements[7] +
                    elements[8] * elements[3] * elements[5];

        temp[15] =  elements[0] * elements[5] * elements[10] -
                    elements[0] * elements[6] * elements[9] -
                    elements[4] * elements[1] * elements[10] +
                    elements[4] * elements[2] * elements[9] +
                    elements[8] * elements[1] * elements[6] -
                    elements[8] * elements[2] * elements[5];

        double determinant = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];
        determinant = 1.0 / determinant;

        for (int i = 0; i < 16; i++)
            elements[i] = temp[i] * determinant;

        return *this;
    }

    // http://www.songho.ca/opengl/gl_projectionmatrix.html
    mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
    {
        mat4 result(1.0f);

        result.elements[0 + 0 * 4] =   2.0f / (right - left);
        result.elements[1 + 1 * 4] =   2.0f / (top - bottom);
        result.elements[2 + 2 * 4] =  -2.0f / (far - near);

        result.elements[0 + 3 * 4] =  -(right + left) / (right - left);
        result.elements[1 + 3 * 4] =  -(top + bottom) / (top - bottom);
        result.elements[2 + 3 * 4] =  -(far + near) / (far - near);

        return result;
    }

    // https://solarianprogrammer.com/2013/05/22/opengl-101-matrices-projection-view-model/
    mat4 mat4::perspective(float fov, float aspectRatio, float near , float far)
    {
        mat4 result(1.0f);

        float top = near * tan((M_PI / 180.0f) * (fov / 2.0f));
        float bottom = -top;
        float right = top * aspectRatio;
        float left = -right;

        result.elements[0 + 0 * 4] = (2.0f * near) / (right - left);    // Wrong value in contrast to GLM::projection matrix
        result.elements[1 + 1 * 4] = (2.0f * near) / (top - bottom);    // Wrong value in contrast to GLM::projection matrix
        result.elements[2 + 2 * 4] = -(far + near) / (far - near);
        result.elements[3 + 3 * 4] = 0.0f;

        result.elements[0 + 2 * 4] = (right + left) / (right - left);
        result.elements[2 + 3 * 4] = -(2.0f * far * near) / (far - near);
        result.elements[3 + 2 * 4] = -1.0f;

        return result;
    }

    mat4 mat4::translation(const vec3& translation)
    {
        mat4 result(1.0f);

        result.elements[0 + 3 * 4] = translation.x;
        result.elements[1 + 3 * 4] = translation.y;
        result.elements[2 + 3 * 4] = translation.z;

        return result;
    }

    mat4 mat4::rotation(float angle, const vec3& axis)
    {
        mat4 result(1.0f);

        float r = toRadians(angle);
        float c = cos(r);
        float s = sin(r);
        float ac = (1.0f - c);

        float x = axis.x;
        float y = axis.y;
        float z = axis.z;

        result.elements[0 + 0 * 4] = x * x * ac + c;
        result.elements[1 + 0 * 4] = y * x * ac + z * s;
        result.elements[2 + 0 * 4] = x * z * ac - y * s;

        result.elements[0 + 1 * 4] = x * y * ac - z * s;
        result.elements[1 + 1 * 4] = y * y * ac + c;
        result.elements[2 + 1 * 4] = y * z * ac + x * s;

        result.elements[0 + 2 * 4] = x * z * ac + y * s;
        result.elements[1 + 2 * 4] = y * z * ac - x * s;
        result.elements[2 + 2 * 4] = z * z * ac + c;

        return result;
    }

    mat4 mat4::scale(const vec3& scale)
    {
        mat4 result(1.0f);

        result.elements[0 + 0 * 4] = scale.x;
        result.elements[1 + 1 * 4] = scale.y;
        result.elements[2 + 2 * 4] = scale.z;

        return result;
    }

	mat4 mat4::LookAt(const vec3& eye, const vec3& target, const vec3& worldUp)
	{
		//vec3 forward    = vec3::normalize(from - to);
		//vec3 right      = vec3::crossProduct(vec3::normalize(worldUp), forward);
		//vec3 up         = vec3::crossProduct(forward, right);

        mat4 camToWorld(1.0f);

    

        return camToWorld;
	}

	std::ostream& operator<<(std::ostream& stream, const mat4& matrix)
    {
        stream << "mat4: \n";
        for(int r = 0; r < 4; r++)
        {
            for(int c = 0; c < 4; c++)
            {
                stream << matrix.elements[r + c * 4] << " ";
            }
            stream << '\n';
        }
        return stream;
    }

} }
