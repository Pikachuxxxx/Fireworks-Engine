#pragma once

#include <iostream>
#include <unordered_map>
// GLEW
#include <GL/glew.h>
#include <src/utils/fileutils.h>
#include <glm/glm.hpp>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fireworks { namespace graphics {

#define SHADER_VERTEX_INDEX  0
#define SHADER_UV_INDEX      1
#define SHADER_TID_INDEX     2
#define SHADER_COLOR_INDEX   3

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
        void setUniform2f(const GLchar* name, const glm::vec2& vector);
        void setUniform3f(const GLchar* name, const glm::vec3& vector);
        void setUniform4f(const GLchar* name, const glm::vec4& vector);
        void setUniformMat4(const GLchar* name, const glm::mat4& matrix);

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
