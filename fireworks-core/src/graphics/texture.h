#pragma once

#include <string>
#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// SOIL - Simple openGL Image Loading Library
#include <SOIL.h>

namespace fireworks { namespace graphics {

    class Texture
    {
    private:
        std::string m_FileName; // Path to the texture source image
        GLuint m_TID; // OpenGL Texture ID
        GLsizei m_Width;
        GLsizei m_Height;

    public:
        Texture(const std::string& path);
        ~Texture();

        void bind() const;
        void unbind() const;

        inline const unsigned int getWidth() const { return m_Width; }
        inline const unsigned int getHeight() const { return m_Height; }
    private:
        GLuint load();
    };

} }
