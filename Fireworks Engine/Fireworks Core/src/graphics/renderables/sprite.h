#pragma once

#include "renderable2d.h"

namespace fireworks { namespace graphics {

    class Sprite : public Renderable2D
    {
    public:
        maths::vec3& position;
        maths::vec4& color;
        uint32_t& frame;
    public:
		Sprite(maths::vec3 position, maths::vec2 size, maths::vec4 color);
		Sprite(maths::vec3 position, maths::vec2 size, Texture* texture);
		Sprite(maths::vec3 position, maths::vec2 size, Texture* texture, maths::vec2 sheetDimension);
    };
} }
