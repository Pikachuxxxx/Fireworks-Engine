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

        renderable->shader->enable();
        renderable->shader->setUniformMat4("view", m_Camera3D->getViewMatrix());

        maths::mat4 model(1.0f);
        model = maths::mat4::translation(transform.position);
        // TODO: Use Quaternions to rotate the 3D primitive 
        model *= maths::mat4::rotation(transform.rotation.x, maths::vec3(1, 0, 0));
        model *= maths::mat4::rotation(transform.rotation.y, maths::vec3(0, 1, 0));
        model *= maths::mat4::rotation(transform.rotation.z, maths::vec3(0, 0, 1));

        float ts = 0.0f;
        if (tid > 0)
            ts = 1.0f;

        // TODO: Query for the primitive and fill the buffer or use the Model<--Mesh to fill the buffer.
        // TODO: Make sure the vertices are Clockwise generated in case we use front face culling.
        // Here primitive denotes the shape of the renderable to be rendered onto the screen not the actual rendering primitives of the 3D renderable.

        if (primitive3d == Primitive3D::Plane)
        {
            /*
             * 3D Plane vs Quad primitive :-
             * Same as that of a sprite but plane doesn't have any kind of face culling.
             * A Quad on the other hand would have face culling enabled by default in
             * contrast to a 3D Plane, which is visible from all sides.
             * A quad is nothing but a sprite viewed in 3D space with front face culling ON.
             * It is also a Cube's bottom face.
             */
            glDisable(GL_CULL_FACE);
            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), 0, (transform.scale.y / 2));
            m_Buffer->uv = uv[0];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), 0, -(transform.scale.y / 2));
            m_Buffer->uv = uv[1];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, 0, -(transform.scale.y / 2));
            m_Buffer->uv = uv[2];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, 0, (transform.scale.y / 2));
            m_Buffer->uv = uv[3];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_IndicesCount += 6;
        }
        else if (primitive3d == Primitive3D::Cube)
        {
            // Face 1 : Front face
            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), -(transform.scale.y / 2), (transform.scale.z / 2));
            m_Buffer->uv = uv[0];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), -(transform.scale.y / 2) + transform.scale.y, (transform.scale.z / 2));
            m_Buffer->uv = uv[1];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, -(transform.scale.y / 2) + transform.scale.y, (transform.scale.z / 2));
            m_Buffer->uv = uv[2];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, -(transform.scale.y / 2), (transform.scale.z / 2));
            m_Buffer->uv = uv[3];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_IndicesCount += 6;

            // Face 2 : Top face
            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), -(transform.scale.y / 2) + transform.scale.y, (transform.scale.z / 2));
            m_Buffer->uv = uv[4];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), -(transform.scale.y / 2) + transform.scale.y, -(transform.scale.z / 2));
            m_Buffer->uv = uv[5];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, -(transform.scale.y / 2) + transform.scale.y, -(transform.scale.z / 2));
            m_Buffer->uv = uv[6];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, -(transform.scale.y / 2) + transform.scale.y, (transform.scale.z / 2));
            m_Buffer->uv = uv[7];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_IndicesCount += 6;

            // Face 3 : Back face
            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), -(transform.scale.y / 2), -(transform.scale.z / 2));
            m_Buffer->uv = uv[0];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), -(transform.scale.y / 2) + transform.scale.y, -(transform.scale.z / 2));
            m_Buffer->uv = uv[1];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, -(transform.scale.y / 2) + transform.scale.y, -(transform.scale.z / 2));
            m_Buffer->uv = uv[2];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, -(transform.scale.y / 2), -(transform.scale.z / 2));
            m_Buffer->uv = uv[3];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_IndicesCount += 6;

            // Face 4 : Bottom face
            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), -(transform.scale.y / 2), (transform.scale.z / 2));
            m_Buffer->uv = uv[4];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), -(transform.scale.y / 2), -(transform.scale.z / 2));
            m_Buffer->uv = uv[5];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, -(transform.scale.y / 2), -(transform.scale.z / 2));
            m_Buffer->uv = uv[6];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, -(transform.scale.y / 2), (transform.scale.z / 2));
            m_Buffer->uv = uv[7];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_IndicesCount += 6;

            // Face 5 : Right face
            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, -(transform.scale.y / 2), (transform.scale.z / 2));
            m_Buffer->uv = uv[4];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, -(transform.scale.y / 2) + transform.scale.y, (transform.scale.z / 2));
            m_Buffer->uv = uv[5];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, -(transform.scale.y / 2) + transform.scale.y, -(transform.scale.z / 2));
            m_Buffer->uv = uv[6];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2) + transform.scale.x, -(transform.scale.y / 2), -(transform.scale.z / 2));
            m_Buffer->uv = uv[7];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_IndicesCount += 6;

            // Face 6 : Left face
            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), -(transform.scale.y / 2), (transform.scale.z / 2));
            m_Buffer->uv = uv[4];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), -(transform.scale.y / 2) + transform.scale.y, (transform.scale.z / 2));
            m_Buffer->uv = uv[5];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), -(transform.scale.y / 2) + transform.scale.y, -(transform.scale.z / 2));
            m_Buffer->uv = uv[6];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), -(transform.scale.y / 2), -(transform.scale.z / 2));
            m_Buffer->uv = uv[7];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_IndicesCount += 6;
        }
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