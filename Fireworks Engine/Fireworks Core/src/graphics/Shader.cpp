#include "shader.h"

namespace fireworks { namespace graphics {

    Shader::Shader(const char* vertexPath, const char* fragmentPath)
        : m_VertPath(vertexPath), m_FragPath(fragmentPath)
    {
        m_ShaderID = load();
    }
    Shader::~Shader()
    {
        glDeleteProgram(m_ShaderID);
    }

    GLuint Shader::load()
    {
        GLuint program  = glCreateProgram();
        GLuint vertex   = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        GLint success;
        GLchar infoLog[1024];

        std::string vertexSourceString = utils::FileUtils::read_file(m_VertPath);
        std::string fragmentSourceString = utils::FileUtils::read_file(m_FragPath);

        const GLchar* vertSource = vertexSourceString.c_str();
        const GLchar* fragSource = fragmentSourceString.c_str();

        glShaderSource(vertex, 1, &vertSource, NULL);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            glDeleteShader(vertex);
        }

        glShaderSource(fragment, 1, &fragSource, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            glDeleteShader(fragment);
        }

        glAttachShader(program, vertex);
        glAttachShader(program, fragment);

        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return program;
    }

    GLint Shader::getUniformLocation(const std::string& name)
    {
        enable();
        if(m_ShaderLocationCache.find(name) != m_ShaderLocationCache.end())
            return m_ShaderLocationCache[name];

        GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        m_ShaderLocationCache[name] = location;
        return location;
    }

    void Shader::setUniform1f(const GLchar* name, float value)
    {
        glUniform1f(getUniformLocation(name), value);
    }

    void Shader::setUniform1fv(const GLchar* name, float* value, GLsizei count)
    {
        glUniform1fv(getUniformLocation(name), count, value);
    }

    void Shader::setUniform1i(const GLchar* name, int value)
    {
        glUniform1i(getUniformLocation(name), value);
    }

    void Shader::setUniform1iv(const GLchar* name, int* value, GLsizei count)
    {
        glUniform1iv(getUniformLocation(name), count, value);
    }

    void Shader::setUniform2f(const GLchar* name, const glm::vec2& vector)
    {
        glUniform2f(getUniformLocation(name), vector.x, vector.y);
    }

    void Shader::setUniform3f(const GLchar* name, const glm::vec3& vector)
    {
        glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
    }

    void Shader::setUniform4f(const GLchar* name, const glm::vec4& vector)
    {
        glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
    }

    void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

	void Shader::enable()
    {
        glUseProgram(m_ShaderID);
    }

    void Shader::disable()
    {
        glUseProgram(0);
    }

} }
