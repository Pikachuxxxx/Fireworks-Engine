#pragma once

#include "renderer3d.h"
#include "renderables/renderable3d.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

namespace fireworks { namespace graphics {
   
#define RENDERER3D_MAX_PRIMITIVES       10000
#define RENDERER3D_VERTEX_SIZE          sizeof(VertexData3D)
#define RENDERER3D_DEFAULT_FACES        6
#define RENDERER3D_PRIMITIVE_SIZE       RENDERER3D_VERTEX_SIZE      * RENDERER3D_DEFAULT_FACES * 4
#define RENDERER3D_BUFFER_SIZE          RENDERER3D_PRIMITIVE_SIZE   * RENDERER3D_MAX_PRIMITIVES
#define RENDERER3D_INDICES_SIZE         RENDERER3D_MAX_PRIMITIVES   * RENDERER3D_DEFAULT_FACES * 6

    class BatchRenderer3D : public Renderer3D
    {
    public:
        Shader*                 shader;
    private:
        GLuint                  m_VAO;
        GLuint                  m_VBO;
        VertexData3D*           m_Buffer;
        IndexBuffer*            m_IBO;
        GLsizei                 m_IndicesCount;
        std::vector<GLuint>     m_TextureSlots;

        GLushort cube_indices[RENDERER3D_INDICES_SIZE];

    public:
        BatchRenderer3D(PerspectiveCamera* camera3D, Shader* shader);
        ~BatchRenderer3D();

        void begin() override;
        void submit(const Renderable3D* renderable) override;
        void end() override;
        void flush() override;
    private:
        void init();
    };

} }
