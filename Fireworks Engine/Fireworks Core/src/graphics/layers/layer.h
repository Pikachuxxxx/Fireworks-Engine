#pragma once

#include "../renderers/renderer2d.h"
#include "../renderers/batchrenderer2d.h"
#include "../renderers/ShotRenderer2D.h"
#include "../renderables/renderable2d.h"

namespace fireworks { namespace graphics {

    /// Creates a Layer to hold a collection of renderables.
    /// 
    /// Add the renderables such as Sprite to the layer and automatically submit it to the render queue
    /// to render them using the renderer of your choice
    class Layer
    {
    public:
        /// The renderer used the by the layer to render the renderables.
        Renderer2D* m_Renderer;
        /// The collection of renderables rendered by the layer.
        std::vector<Renderable2D*> m_Renderables;
    public:
        /// Create the layer by passing the renderer of your choice.
        /// 
        /// @param renderer The render of your choice
        /// @see Renderer2D for more information of the renderer's available
        Layer(Renderer2D* renderer);
        virtual ~Layer();
        /// Use this to add the renderables to the layer
        virtual void add(Renderable2D* renderable);
        /// Renders all the renderables present in the layer
        virtual void render();

        /// Gets the list of renderables in the layer
        /// 
        /// @returns A reference to list of renderables present in the layer
        inline const std::vector<Renderable2D*>&  getRenderables() { return m_Renderables; }
    };

} }
