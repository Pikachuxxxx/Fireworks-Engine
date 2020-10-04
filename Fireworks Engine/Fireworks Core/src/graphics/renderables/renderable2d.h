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
        mutable int m_Frame;
    protected:
        maths::vec3 m_Position;
        maths::vec2 m_Size;
        maths::vec4 m_Color;
        mutable std::vector<maths::vec2> m_UV;
        Texture* m_Texture;
    protected:
        Renderable2D() : m_Texture(nullptr) { setUVDefaults(); }
    public:
        Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color)
            : m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr), m_Frame(1)
        { 
            setUVDefaults();
        }

		Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color, int linearFrameIndex)
			: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr), m_Frame(linearFrameIndex)
		{
			//setUVFrame(linearFrameIndex, maths::vec2(m_Texture->getWidth(), m_Texture->getHeight()));
			setUVFrame();
		}

        virtual ~Renderable2D() { }

        virtual void submit(Renderer2D* renderer) const
        {
            setUVFrame();
            renderer->submit(this);
        }

        void setUVFrame() const
        {
			m_UV.clear();
            float x = m_Frame, y = 0;
			maths::vec2 texSize = maths::vec2(50.0f, 75.0f);
            float frameWidth = texSize.x / 2.0f, frameHeight = texSize.y;
			m_UV.push_back(maths::vec2((x * frameWidth) / texSize.x, (y * frameHeight) / texSize.y)); // Bottom Left
			m_UV.push_back(maths::vec2((x * frameWidth) / texSize.x, ((y + 1) * frameHeight) / texSize.y)); // Top Left
			m_UV.push_back(maths::vec2(((x + 1) * frameWidth) / texSize.x, ((y + 1) * frameHeight) / texSize.y)); // Top Right
			m_UV.push_back(maths::vec2(((x + 1) * frameWidth) / texSize.x, (y * frameHeight) / texSize.y)); // Bottom Right
        }

        inline const maths::vec3& getPosition() const { return m_Position; }
        inline const maths::vec2& getSize() const { return m_Size; }
        inline const maths::vec4& getColor() const { return m_Color; }
        inline const std::vector<maths::vec2>& getUV() const { return m_UV; }
        inline const GLuint getTID() const { return m_Texture == nullptr ? 0 : m_Texture->getID(); }
    private:
        void setUVDefaults() const
        {
            m_UV.clear();
            m_UV.push_back(maths::vec2(0, 0)); // Bottom Left
            m_UV.push_back(maths::vec2(0, 1)); // Top Left
			m_UV.push_back(maths::vec2(0.5, 1)); // Top Right
			m_UV.push_back(maths::vec2(0.5, 0)); // Bottom Right
        }

        //void setUVFrame(int index, const maths::vec2& texSize)
    };

} }
