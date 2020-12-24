#pragma once

#include "renderer3d.h"
#include "../renderables/renderable3d.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

namespace fireworks { namespace graphics {

#define SHOT_RENDERER3D_MAX_PRIMITIVES      1
#define SHOT_RENDERER3D_VERTEX_SIZE         sizeof(VertexData3D)
#define SHOT_RENDERER3D_DEFAULT_FACES       6
#define SHOT_RENDERER3D_PRIMITIVE_SIZE      SHOT_RENDERER3D_VERTEX_SIZE    * SHOT_RENDERER3D_DEFAULT_FACES * 4
#define SHOT_RENDERER3D_BUFFER_SIZE         SHOT_RENDERER3D_PRIMITIVE_SIZE * SHOT_RENDERER3D_MAX_PRIMITIVES
#define SHOT_RENDERER3D_INDICES_SIZE        SHOT_RENDERER3D_MAX_PRIMITIVES * SHOT_RENDERER3D_DEFAULT_FACES * 6

    class ShotRenderer3D : public Renderer3D
    {
    private: 
        GLuint          m_VAO;
        GLuint          m_VBO;
        VertexData3D*   m_Buffer;
        IndexBuffer*    m_IBO;
        GLsizei         m_IndicesCount;
        GLuint			m_Texture;
    public:
        ShotRenderer3D(PerspectiveCamera* camera);
        ~ShotRenderer3D();

        /// Begins the rendering process
        void begin() override;
        /// Begins to submit the renderables to render queue
        void submit(const Renderable3D* renderable) override;
        /// Ends the submission and prepares the renderer to start drawing 
        void end() override;
        /// Draws the data processed onto the screen
        void flush(const IndexBuffer* ibo = nullptr) override;
    private:
        void init();
    };

} }

