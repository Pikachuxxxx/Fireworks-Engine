#pragma once

#include <deque>
#include "renderables/static_sprite.h"
#include "renderables/renderable2d.h"

namespace fireworks { namespace graphics {

    class Simple2DRenderer : public Renderer2D
    {
    private:
        std::deque<const StaticSprite*> m_RenderQueue;
    public:
        void submit(const Renderable2D* renderable) override;
        void flush() override;
    };

} }
