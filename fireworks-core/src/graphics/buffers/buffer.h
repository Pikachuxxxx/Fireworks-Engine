#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

namespace fireworks { namespace graphics {

        class Buffer
        {
        private:
            GLuint m_BufferID;
            GLuint m_ComponentCount;
        public:
            Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
            ~Buffer();
            
            void bind() const;
            void unbind() const;

            inline GLuint getComponentCount() const { return m_ComponentCount; }
        };
} }
