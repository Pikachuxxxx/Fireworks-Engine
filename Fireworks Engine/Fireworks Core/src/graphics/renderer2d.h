#pragma once

#include <vector>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "camera2d.h"
#include "Shader.h"
#include "../maths/maths.h"

namespace fireworks { namespace graphics {

#define SHADER_VERTEX_INDEX  0
#define SHADER_UV_INDEX      1
#define SHADER_TID_INDEX     2
#define SHADER_COLOR_INDEX   3

    class Renderable2D;    // Forward declaration

    class Renderer2D
    {
    public:
        Camera2D*                   m_Camera2D; 
    protected:
        std::vector<maths::mat4>    m_TransformationStack;
  const maths::mat4*                m_TransformationBack;
        // GLuint                   m_FontTexture;
    protected:
        Renderer2D(Camera2D* camera2D)
            : m_Camera2D(camera2D)
        {
            m_TransformationStack.push_back(maths::mat4::identity());
            m_TransformationBack = &m_TransformationStack.back();
        }
    public:
        void push(const maths::mat4& matrix, bool override = false)
        {
            if(override)
                m_TransformationStack.push_back(matrix);
            else
                m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

            m_TransformationBack = &m_TransformationStack.back();
        }
        void pop()
        {
            // TODO: Add to logging system
            if(m_TransformationStack.size() > 1)
                m_TransformationStack.pop_back();

            m_TransformationBack = &m_TransformationStack.back();
        }
        virtual ~Renderer2D() { }
        virtual void begin() {}
        virtual void submit(const Renderable2D* renderable) = 0;
        virtual void drawString(const std::string& text, const maths::vec3& position, const maths::vec4& color) { }
        virtual void end() {}
        virtual void flush() = 0;
    };

} }
