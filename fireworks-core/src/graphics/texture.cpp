#include "texture.h"

namespace fireworks { namespace graphics {

    Texture::Texture(const std::string& filename)
        : m_FileName(filename)
    {
        m_TID = load();
    }

    Texture::~Texture()
    {

    }

    GLuint Texture::load()
    {
        // BYTE* pixels = utils::load_image(m_FileName.c_str(), &m_Width, &m_Height);
        unsigned char* image = SOIL_load_image(m_FileName.c_str(), &m_Width, &m_Height, 0, SOIL_LOAD_RGB);

        GLuint result;
        glGenTextures(1, &result);
        glBindTexture(GL_TEXTURE_2D, result);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        SOIL_free_image_data(image);

        return result;
    }

    void Texture::bind() const
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_TID);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

} }
