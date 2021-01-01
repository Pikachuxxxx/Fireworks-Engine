#include "texture.h"
// stb_image
#define STB_IMAGE_IMPLEMENTATION
#include "../../vendor/stb_image/stb_image.h"

namespace fireworks { namespace graphics {

    Texture::Texture(const std::string& filename, bool flip /*= true*/, const std::string& typeName /*= "texture_diffuse"*/)
        : m_FileName(filename), m_TID(0), m_Width(0), m_Height(0), m_BPP(0), m_FlipTexture(flip)
    {
        m_TID = load();
    }

    Texture::~Texture()
    {
        // TODO: Fix the memory leak for textures deallocation
    }

    GLuint Texture::load()
    {

        stbi_set_flip_vertically_on_load(m_FlipTexture);
        unsigned char* image = stbi_load(m_FileName.c_str(), &m_Width, &m_Height, &m_BPP, 4);
      
        if (!image)
        {
            std::cout << "ERROR::TEXTURE::Failed loading Image" << std::endl;
            return NULL;
        }

        GLuint result = 0;
        glGenTextures(1, &result);
        glBindTexture(GL_TEXTURE_2D, result);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(image);

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
