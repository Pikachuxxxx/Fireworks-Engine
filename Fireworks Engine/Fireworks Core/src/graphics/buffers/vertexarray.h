#pragma once

#include <vector>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include "buffer.h"

namespace fireworks { namespace graphics {

    /// Creates Vertex Array Object (VAOs).
    class VertexArray
    {
    private:
        GLuint m_ArrayID;
        std::vector<Buffer*> m_Buffers;
    public:
        /// Generates VAO
        VertexArray();
        ~VertexArray();

        /// Adds the the vertex buffer (VBO) to the VAO.
        /// 
        /// @param buffer The vertex buffer containing the vertex data of the geometry
        /// @param index To which Attribute the corresponding buffers corresponds to
        void addBuffer(Buffer* buffer, GLuint index);
        /// Binds the vertex array
        void bind() const;
        /// Unbind the vertex array
        void unbind() const;
    };

} }
