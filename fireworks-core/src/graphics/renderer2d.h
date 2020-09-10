#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include "../maths/maths.h"
#include "renderable2d.h"


namespace fireworks { namespace graphics {

    class Renderer2D
    {
    public:
        virtual ~Renderer2D() { }

        virtual void begin() {}
        virtual void submit(const Renderable2D* renderable) = 0;
        virtual void end() {}
        virtual void flush() = 0;
    };

} }
