#pragma once

#include "../renderer2d.h"
#include "../renderables/renderable2d.h"

namespace fireworks { namespace graphics {

    class Layer
    {
    public:
        Renderer2D* m_Renderer;
        std::vector<Renderable2D*> m_Renderables;
    public:
        Layer(Renderer2D* renderer);
        virtual ~Layer();
        virtual void add(Renderable2D* renderable);
        virtual void render();

        inline const std::vector<Renderable2D*>&  getRenderables() { return m_Renderables; }
    };

} }
