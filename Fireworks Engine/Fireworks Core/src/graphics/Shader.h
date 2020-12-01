#pragma once

#include <iostream>
#include <unordered_map>
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

    /// The class responsible for creating amazing shaders
    class Shader
    {
    public:
        /// The ID of the shader
        GLuint m_ShaderID;
        /// Path to the vertex shader file
        const char* m_VertPath;
        /// Path to the fragment shader file
        const char* m_FragPath;
    private:
        std::unordered_map<std::string, GLint> m_ShaderLocationCache;
    public:
        /// Creates the shader by taking in the vertex and fragment shader files
        ///
        /// @param vertexPath The path to the vertex shader file
		/// @param fragmentPath The path to the fragment shader file
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

        /// Enables the shader
        void enable();
		/// Disables the shader
        void disable();

        /// Gets the shaders Program
        inline GLint getShaderProgram() const { return m_ShaderID; }
    private:
        GLuint load();
        GLint getUniformLocation(const std::string& name);
    };

} }
