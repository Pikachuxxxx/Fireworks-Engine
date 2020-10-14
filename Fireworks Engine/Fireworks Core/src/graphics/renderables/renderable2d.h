#pragma once

#include "../shader.h"
#include "../buffers/buffer.h"
#include "../buffers/indexbuffer.h"
#include "../buffers/vertexarray.h"
#include "../../maths/maths.h"
#include "../renderer2d.h"
#include "../texture.h"

namespace fireworks { namespace graphics {

    struct VertexData
    {
        maths::vec3 vertex;
        maths::vec2 uv;
        float tid;
        maths::vec4 color;
    };

    class Renderable2D
    {
    public:
        Shader*                             m_Shader;
		bool                                flippedX;
		bool                                flippedY;
    protected:
		maths::vec2                         m_Size;
		maths::vec3                         m_Position;
		maths::vec4                         m_Color;
mutable std::vector<maths::vec2>            m_UV;
		Texture*                            m_Texture;
    public:
        Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color, Shader* shader)
            : m_Position(position), m_Size(size), m_Color(color), m_Shader(shader), m_Texture(nullptr)
        { 
			m_Shader->enable();
			GLint texIDs[] =
			{
				0, 1,  2,  3,  4,  5,  6,  7,
				8, 9, 10, 11, 12, 13, 14, 15
			};
			m_Shader->setUniform1iv("textures", texIDs, 8);
			m_Shader->disable();

            setUVDefaults();
        }

        virtual ~Renderable2D() { }

        virtual void submit(Renderer2D* renderer) const
        {
            renderer->submit(this);
        }

        inline const maths::vec2& getSize() const { return m_Size; }
        inline const maths::vec3& getPosition() const { return m_Position; }
        inline const maths::vec4& getColor() const { return m_Color; }
        inline const std::vector<maths::vec2>& getUV() const { return m_UV; }
        inline const GLuint getTID() const { return m_Texture == nullptr ? 0 : m_Texture->getID(); }
        
        // Custom Methods
        void flipX() { flippedX = true; }
        void unflipX() { flippedX = false; }

        void flipY() { flippedY = true; }
        void unflipY() { flippedY = false; }

	protected:
		Renderable2D() : m_Texture(nullptr) { setUVDefaults(); }
	private:
		void setUVDefaults()
		{
			m_UV.push_back(maths::vec2(0, 0));  // Bottom Left
			m_UV.push_back(maths::vec2(0, 1));  // Top Left
            m_UV.push_back(maths::vec2(1, 1));  // Top Right
            m_UV.push_back(maths::vec2(1, 0));  // Bottom Right
        }


    };

} }
 