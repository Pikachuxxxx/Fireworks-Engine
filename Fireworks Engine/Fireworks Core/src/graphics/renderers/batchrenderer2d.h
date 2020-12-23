#pragma once

#include <cstddef>

#include "../renderables/renderable2d.h"
#include "renderer2d.h"

// #include <FTGL/ftgl.h>
#define GLT_IMPLEMENTATION
#include "../../../ext/gltext.h"

namespace fireworks { namespace graphics {

#define RENDERER_MAX_SPRITES    60000
#define RENDERER_VERTEX_SIZE    sizeof(VertexData)
#define RENDERER_SPRITE_SIZE    RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE    RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE   RENDERER_MAX_SPRITES * 6

    /// Renders the renderables in a single draw call using batching.
    class BatchRenderer2D : public Renderer2D
    {
    public:
        /// The shader with which the batch will be rendered with
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
        /// Creates the batch renderer 
        /// 
        /// @param camera2D The graphics::Camera2D to which the rendered view will be relayed to
        /// @param shader The shader with which the batch will be rendered with
        /// @see graphics::Camera2D for more information on creating the camera
        /// @see graphics::shader for more informatoin of creating shaders
        BatchRenderer2D(Camera2D* camera2D, Shader* shader);
        ~BatchRenderer2D();

        /// Begins the rendering process
        void begin() override;
        /// Begins to submit the renderables to render queue
        void submit(const Renderable2D* renderable) override;
        /// Ends the submission and prepares the renderer to start drawing 
        void end() override;
        /// Draws the data processed onto the screen
        void flush() override;
    private:
        void init();
    };

} }
