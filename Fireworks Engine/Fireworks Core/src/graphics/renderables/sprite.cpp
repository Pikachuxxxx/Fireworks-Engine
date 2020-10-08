#include "sprite.h"

namespace fireworks { namespace graphics {

	Sprite::Sprite(maths::vec3 position, maths::vec2 size, maths::vec4 color)
        : Renderable2D(position, size, color), position(m_Position), color(m_Color), frame(m_Frame)
    {

    }

    Sprite::Sprite(maths::vec3 position, maths::vec2 size, Texture* texture)
        : Renderable2D(position, size, maths::vec4(1, 0, 1, 1)), position(m_Position), color(m_Color), frame(m_Frame)
    {
        m_Texture = texture;
    }

	Sprite::Sprite(maths::vec3 position, maths::vec2 size, Texture* texture, maths::vec2 sheetDimension)
        : Renderable2D(position, size, maths::vec4(1, 0, 1, 1)), position(m_Position), color(m_Color), frame(m_Frame)
	{
		m_Texture = texture;
	    m_SpriteSheetDimension = sheetDimension;
	}

} }
