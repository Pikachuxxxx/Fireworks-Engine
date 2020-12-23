#pragma once

#include <vector>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "../Shader.h"
#include "../../maths/maths.h"
#include "../perspectivecamera.h"

namespace fireworks { namespace graphics {

    class Renderable3D;    /// Forward declaration of the graphics::Renderable3D

    /// The renderer base class from which different 3D renderers are derived from
    class Renderer3D
    {
    public:
        /// The camera to which the renderers out will be displayed to
        PerspectiveCamera* m_Camera3D;
    protected:
        /// Creates the renderer using the camera
        /// 
        /// @param camera3D The camera to be used with the renderer
        Renderer3D(PerspectiveCamera* camera3D) : m_Camera3D(camera3D) { }
    public:
        virtual ~Renderer3D() { }
        /// Begins the rendering process
        virtual void begin() {}
        /// Begins to submit the renderables to render queue
        virtual void submit(const Renderable3D* renderable) = 0;
        /// Ends the submission and prepares the renderer to start drawing 
        virtual void end() {}
        /// Draws the data processed onto the screen
        virtual void flush() = 0;
    };

} }
