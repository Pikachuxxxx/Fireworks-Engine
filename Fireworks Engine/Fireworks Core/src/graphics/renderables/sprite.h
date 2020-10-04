#pragma once

#include "renderable2d.h"

namespace fireworks { namespace graphics {

    class Sprite : public Renderable2D
    {
    public:
        maths::vec3& position;
        maths::vec4& color;
        int& sprframe;
    public:
        Sprite(float x, float y, float width, float height, maths::vec4 color);
        Sprite(float x, float y, float width, float height, Texture* texture);
        Sprite(float x, float y, float width, float height, Texture* texture, int frame);
    };
} }
