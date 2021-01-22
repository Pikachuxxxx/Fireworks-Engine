#pragma once

#include "renderer3d.h"
#include "../renderables/renderable3d.h"

#include "../../utils/glassert.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

namespace fireworks { namespace graphics {

// TODO: Rename these to more understandable and meaningful names
#define RENDERER3D_MAX_PRIMITIVES       2000
#define RENDERER3D_VERTEX_SIZE          sizeof(VertexData3D)
#define RENDERER3D_DEFAULT_FACES        6
#define RENDERER3D_PRIMITIVE_SIZE       RENDERER3D_VERTEX_SIZE    * RENDERER3D_DEFAULT_FACES * 4
#define RENDERER3D_BUFFER_SIZE          RENDERER3D_PRIMITIVE_SIZE * RENDERER3D_MAX_PRIMITIVES
#define RENDERER3D_INDICES_SIZE         RENDERER3D_MAX_PRIMITIVES * RENDERER3D_DEFAULT_FACES * 6

    /// Renders the 3d renderables in a single draw call using batching.
    class BatchRenderer3D : public Renderer3D
    {
    public:
        /// The shader with which the entire batch or renderables are rendered with
        Shader*                     shader;
    private:
        GLuint                      m_VAO;
        GLuint                      m_VBO;
        IndexBuffer*                m_IBO;
        GLsizei                     m_IndicesCount;
        std::vector<GLuint>         m_TextureSlots;

        std::vector<unsigned int>   m_IndicesPool;
        VertexData3D*               m_Buffer;

        unsigned int indexOffset;
    public:
        /// Creates a 3D batch renderer
        ///
        /// @param camera3D The 3d camera object to which the scene is to be renderer to
        /// @param shader The shader with which the whole bathc is renderer with
        BatchRenderer3D(PerspectiveCamera* camera3D, Shader* shader);
        ~BatchRenderer3D();

        /// Begins the rendering process
        void begin() override;
        /// Submits the data to the render queue
        void submit(const Renderable3D* renderable) override;
        /// Ends the submission and prepares the renderer to start drawing 
        void end() override;
        /// Draws the data processed onto the screen
        void flush() override;
    protected:
        void init();
    };

} }
