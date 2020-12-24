#pragma once

#include "renderables/renderable3d.h"
#include "renderers/renderer3d.h"
#include "renderers/batchrenderer3d.h"
#include "renderers/shotrenderer3d.h"
#include "model.h"

namespace fireworks { namespace graphics {

    class Scene3D
    {
        // TODO: Use const getter functions and make them private
    public:
        Renderer3D*                 renderer;
        std::vector<Renderable3D*>  renderables;
    public:
        Scene3D(Renderer3D* renderer);
        virtual ~Scene3D();

        virtual void add(Renderable3D* renderable);
        virtual void render();

        inline const std::vector<Renderable3D*>& getRendetables() const { return renderables; }
    };

} }