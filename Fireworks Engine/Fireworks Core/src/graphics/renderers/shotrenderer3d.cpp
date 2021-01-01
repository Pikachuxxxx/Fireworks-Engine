#include "shotrenderer3d.h"

namespace fireworks { namespace graphics {

    ShotRenderer3D::ShotRenderer3D(PerspectiveCamera* camera)
        :Renderer3D(camera)
    {
        init();
    }

    ShotRenderer3D::~ShotRenderer3D()
    {
        delete m_IBO;
        glDeleteBuffers(1, &m_VBO);
    }

    void ShotRenderer3D::init()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, SHOT_RENDERER3D_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
        glEnableVertexAttribArray(SHADER_UV_INDEX);
        glEnableVertexAttribArray(SHADER_TID_INDEX);
        glEnableVertexAttribArray(SHADER_COLOR_INDEX);
        glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, SHOT_RENDERER3D_VERTEX_SIZE, (const GLvoid*)0);
        glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, SHOT_RENDERER3D_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
        glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, SHOT_RENDERER3D_VERTEX_SIZE, (const GLvoid*)(5 * sizeof(GLfloat)));
        glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, SHOT_RENDERER3D_VERTEX_SIZE, (const GLvoid*)(6 * sizeof(GLfloat)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        GLushort indices[SHOT_RENDERER3D_INDICES_SIZE];

        for (int i = 0; i < SHOT_RENDERER3D_INDICES_SIZE; i += 6)
        {
            indices[  i  ] = 0;
            indices[i + 1] = 1;
            indices[i + 2] = 2;

            indices[i + 3] = 2;
            indices[i + 4] = 3;
            indices[i + 5] = 0;
        }

        m_IBO = new IndexBuffer(indices, SHOT_RENDERER3D_INDICES_SIZE);

        glBindVertexArray(0);
    }

    void ShotRenderer3D::begin()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        m_Buffer = (VertexData3D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    }

    void ShotRenderer3D::submit(const Renderable3D* renderable)
    {
        const Transform& transform = renderable->getTransform();
        const maths::vec4& color = renderable->getColor();
        const std::vector<maths::vec2>& uv = renderable->getUV();
        const unsigned int tid = renderable->getTID();
        const Primitive3D& primitive3d = renderable->gerPrimitive();
        std::vector<VertexData3D> vertices = renderable->getVerts();

        maths::mat4 model(1.0f);
        model = maths::mat4::translation(transform.position);
        // TODO: Use Quaternions to rotate the 3D primitive 
        model *= maths::mat4::rotation(transform.rotation.x, maths::vec3(1, 0, 0));
        model *= maths::mat4::rotation(transform.rotation.y, maths::vec3(0, 1, 0));
        model *= maths::mat4::rotation(transform.rotation.z, maths::vec3(0, 0, 1));

        float ts = 0.0f;
        if (tid > 0)
            ts = 1.0f;

        for (int i = 0; i < renderable->getVertsSize(); i++)
        {
            // TODO: Make sure the vertices are Clockwise generated in case we use front face culling.
            m_Buffer->vertex = (model * vertices[i].vertex);
            m_Buffer->uv = vertices[i].uv;
            m_Buffer->tid = ts;
            m_Buffer->color = vertices[i].color;
            m_Buffer++;
        }
        m_IndicesCount += renderable->getIndicesSize();
    }

    void ShotRenderer3D::end()
    {
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void ShotRenderer3D::flush()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Texture);
        glBindVertexArray(m_VAO);
        m_IBO->bind();

        glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_SHORT, NULL);

        m_IBO->unbind();
        glBindVertexArray(0);

        m_IndicesCount = 0;
    }


} }