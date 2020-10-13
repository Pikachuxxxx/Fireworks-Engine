#pragma once

#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include "../utils/fileutils.h"
#include "../maths/maths.h"
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fireworks { namespace graphics {

    class Shader
    {
    private:
        GLuint m_ShaderID;
        const char* m_VertPath;
        const char* m_FragPath;
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        void setUniform1f(const GLchar* name, float value);
        void setUniform1fv(const GLchar* name, float* value, GLsizei count);
        void setUniform1i(const GLchar* name, int value);
        void setUniform1iv(const GLchar* name, int* value, GLsizei count);
        void setUniform2f(const GLchar* name, const maths::vec2& vector);
        void setUniform3f(const GLchar* name, const maths::vec3& vector);
        void setUniform4f(const GLchar* name, const maths::vec4& vector);
        void setUniformMat4(const GLchar* name, const maths::mat4& matrix);
		void setUniformglmMat4(const GLchar* name, const glm::mat4& matrix);

        void enable();
        void disable();

        inline GLint getShaderProgram() const { return m_ShaderID; }
    private:
        GLuint load();
        GLint getUniformLocation(const GLchar* name);
    };

} }
