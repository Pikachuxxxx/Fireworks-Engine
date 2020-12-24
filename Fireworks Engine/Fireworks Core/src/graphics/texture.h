#pragma once

#include <string>
#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

namespace fireworks { namespace graphics {

    /// The class responsible for loading Textures
    class Texture
    {
    public:
    private:
        std::string m_FileName; // Path to the texture source image
        std::string m_TypeName;
        GLuint m_TID; // OpenGL Texture ID
        GLsizei m_Width;
        GLsizei m_Height;
        GLsizei m_BPP;
    public:
        /// Creates Textures from images
        /// 
        /// @param path The file path to the image/texture
        /// @warning Currently only supports .png files
        Texture(const std::string& path, const std::string& typeName = "texture_diffuse");
        ~Texture();

        /// Binds the texture
        void bind() const;
        /// Unbinds the texture
        void unbind() const;

        /// Gets the Width of the texture 
        inline const unsigned int getWidth() const { return m_Width; }
        /// Gets the Height of the texture
        inline const unsigned int getHeight() const { return m_Height; }
        /// Gets the ID of the texture
        inline const unsigned int getID() const { return m_TID; }
        /// Gets the path of the texture
        inline const std::string getPath() const { return m_FileName; }
        /// Return the name of the texture's type
        inline const std::string getTypeName() const { return m_TypeName; }
    private:
        GLuint load();
    };

} }
