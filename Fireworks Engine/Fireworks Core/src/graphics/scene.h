#pragma once

#include "renderables/renderable3d.h"
#include "renderer3d.h"
#include "batchrenderer3d.h"

namespace fireworks { namespace graphics {

    class Scene
    {
        // TODO: Use const getter functions and make them private
    public:
        Renderer3D*                 m_Renderer;
        std::vector<Renderable3D*>  m_Renderables;
    public:
        Scene(Renderer3D* renderer);
        virtual ~Scene();

        virtual void add(Renderable3D* renderable);
        virtual void render();

        inline const std::vector<Renderable3D*>& getRendetables() const { return m_Renderables; }
    };

} }