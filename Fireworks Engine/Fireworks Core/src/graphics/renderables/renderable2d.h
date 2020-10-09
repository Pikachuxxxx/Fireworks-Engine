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
    protected:
		maths::vec2                         m_Size;
		maths::vec3                         m_Position;
		maths::vec4                         m_Color;
        mutable std::vector<maths::vec2>    m_UV;
		Texture*                            m_Texture;
    public:
        Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color)
            : m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr)
        { 
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
 