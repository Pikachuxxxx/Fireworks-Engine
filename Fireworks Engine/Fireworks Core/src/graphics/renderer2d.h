#pragma once

#include <vector>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "camera2d.h"
#include "Shader.h"
#include "../maths/maths.h"

namespace fireworks { namespace graphics {

    class Renderable2D;    /// Forward declaration of the graphics::Renderable2D

    /// The renderer base class from which different renderers are derived from
    class Renderer2D
    {
    public:
        /// The camera to which the renderers out will be displayed to
        Camera2D*                   m_Camera2D; 
    protected:
        /// The transformation matrix stack that keeps track of relative transformation matrix of the groups
        std::vector<maths::mat4>    m_TransformationStack;
        /// The transformation matrix to renders stuff relative to one another aka if using groups
  const maths::mat4*                m_TransformationBack;
        // GLuint                   m_FontTexture;
    protected:
        /// Creates the renderer using the camera
        /// 
        /// @param camera2D The camera to be used with the renderer
        Renderer2D(Camera2D* camera2D)
            : m_Camera2D(camera2D)
        {
            m_TransformationStack.push_back(maths::mat4::identity());
            m_TransformationBack = &m_TransformationStack.back();
        }
    public:
        /// Pushes the transformation matrix to transform the renderables if using groups
        void push(const maths::mat4& matrix, bool override = false)
        {
            if(override)
                m_TransformationStack.push_back(matrix);
            else
                m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

            m_TransformationBack = &m_TransformationStack.back();
        }
		/// Pops the transformation matrix to transform the renderables if using groups
        void pop()
        {
            // TODO: Add to logging system
            if(m_TransformationStack.size() > 1)
                m_TransformationStack.pop_back();

            m_TransformationBack = &m_TransformationStack.back();
        }

        virtual ~Renderer2D() { }
		/// Begins the rendering process
        virtual void begin() {}
		/// Begins to submit the renderables to render queue
        virtual void submit(const Renderable2D* renderable) = 0;
		/// Ends the submission and prepares the renderer to start drawing 
        virtual void end() {}
		/// Draws the data processed onto the screen
        virtual void flush() = 0;
    };

} }
