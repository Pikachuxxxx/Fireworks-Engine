#pragma once

#include "renderables/renderable3d.h"
#include "renderers/renderer3d.h"
#include "renderers/batchrenderer3d.h"
#include "renderers/shotrenderer3d.h"
#include "model.h"

namespace fireworks { namespace graphics {

    /// The scene object that contains information about the 3d rendering and renderables objects.
    ///
    /// It stores all the renderables and information about renderable3d objects, also takes care of render queuing
    class Scene3D
    {
        // TODO: Use const getter functions and make them private
    public:
        /// The Renderer3D used by the scene to render the 3d renderables
        Renderer3D*                 renderer;
        /// The list of 3d renderables that are present in the scene
        std::vector<Renderable3D*>  renderables;
    public:
        /// Creates a 3D scene to store 3d renderable objects
        ///
        /// @param renderer The 3DRenderer to use to render the 3d objects
        Scene3D(Renderer3D* renderer);

        /// <summary>
        /// Destructor of the scene
        /// </summary>
        virtual ~Scene3D();

        /// Adds 3D renderables to the scene
        ///
        /// @param renderable The renderable object to be rendered in the scene
        virtual void add(Renderable3D* renderable);

        /// Renders the scene by submitting it's renderables to the renderer's render queue
        virtual void render();

        /// Gets a reference to the pool of renderables in the scene
        inline const std::vector<Renderable3D*>& getRendetables() const { return renderables; }
    private:
        void sortOnIBOSimilarity(Renderable3D* renderable);

    };

} }