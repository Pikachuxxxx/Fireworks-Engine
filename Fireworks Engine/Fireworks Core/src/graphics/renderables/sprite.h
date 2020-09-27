#pragma once

#include "renderable2d.h"

namespace fireworks { namespace graphics {

    class Sprite : public Renderable2D
    {
    public:
        maths::vec3& position;
    public:
        Sprite(float x, float y, float width, float height, maths::vec4 color);
        Sprite(float x, float y, float width, float height, Texture* texture);
    };
} }
