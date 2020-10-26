#pragma once

#include <cstddef>

#include "renderables/renderable2d.h"
#include "renderer2d.h"

// #include <FTGL/ftgl.h>
#define GLT_IMPLEMENTATION
#include "../../ext/gltext.h"

namespace fireworks { namespace graphics {

#define RENDERER_MAX_SPRITES    60000
#define RENDERER_VERTEX_SIZE    sizeof(VertexData)
#define RENDERER_SPRITE_SIZE    RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE    RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE   RENDERER_MAX_SPRITES * 6

    class BatchRenderer2D : public Renderer2D
    {
    public:
        Shader*                 m_Shader;
    private:
        GLuint                  m_VAO;
        GLuint                  m_VBO;
        VertexData*             m_Buffer;
		IndexBuffer*            m_IBO;
		//IndexBuffer* m_TIBO;
        GLsizei                 m_IndicesCount;
        std::vector<GLuint>     m_TextureSlots;

		GLushort quad_indices[RENDERER_INDICES_SIZE];
		//GLushort tris_indices[RENDERER_INDICES_SIZE];

        GLTtext*                m_Text;
    public:
        BatchRenderer2D(Camera2D* camera2D, Shader* shader);
        ~BatchRenderer2D();
        void begin() override;
        void submit(const Renderable2D* renderable) override;
        void end() override;
        void flush() override;
    private:
        void init();
    };

} }
