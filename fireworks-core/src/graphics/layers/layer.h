#pragma once

#include "../renderer2d.h"
#include "../renderable2d.h"

namespace fireworks { namespace graphics {

    class Layer
    {
    public:
        Renderer2D* m_Renderer;
        std::vector<Renderable2D*> m_Renderables;
        Shader* m_Shader;
        maths::mat4 m_ProjectionMatrix;
    public:
        Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix);
    public:
        virtual ~Layer();
        virtual void add(Renderable2D* renderable);
        virtual void render();
    };

} }
