#pragma once

#include <vector>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include "buffer.h"

namespace fireworks { namespace graphics {

    class VertexArray
    {
    private:
        GLuint m_ArrayID;
        std::vector<Buffer*> m_Buffers;
    public:
        VertexArray();
        ~VertexArray();

        void addBuffer(Buffer* buffer, GLuint index);
        void bind() const;
        void unbind() const;
    };

} }
