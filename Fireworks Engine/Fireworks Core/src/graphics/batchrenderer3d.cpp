#include "batchrenderer3d.h"

namespace fireworks { namespace graphics {
    
    std::uint32_t Renderable3D::m_UniqueID = 0;

    BatchRenderer3D::BatchRenderer3D(PerspectiveCamera* camera3D, Shader* shader)
        : Renderer3D(camera3D), shader(shader)
    {
        init();
        this->shader->enable();
        glm::mat4 proj = glm::perspective(camera3D->FOV, camera3D->aspectRatio, camera3D->nearClipping, camera3D->farClipping); 
        std::cout << "GLM Projections matrix is : " << (glm::to_string(proj)) << std::endl;
        std::cout << "custom projections matrix is : " << camera3D->getProjectionMatrix() << std::endl;
        this->shader->setUniformglmMat4("projection", proj);

        GLint texIDs[] =
        {
            0, 1,  2,  3,  4,  5,  6,  7,
            8, 9, 10, 11, 12, 13, 14, 15
        };
        this->shader->setUniform1iv("textures", texIDs, 8);
        this->shader->disable();
    }

    void BatchRenderer3D::init()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, RENDERER3D_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
        glEnableVertexAttribArray(SHADER_UV_INDEX);
        glEnableVertexAttribArray(SHADER_TID_INDEX);
        glEnableVertexAttribArray(SHADER_COLOR_INDEX);
        glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER3D_VERTEX_SIZE, (const GLvoid*)0);
        glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER3D_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
        glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER3D_VERTEX_SIZE, (const GLvoid*)(5 * sizeof(GLfloat)));
        glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER3D_VERTEX_SIZE, (const GLvoid*)(6 * sizeof(GLfloat)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        int offset = 0;
        for (int i = 0; i < RENDERER3D_INDICES_SIZE; i += 6)
        {
            cube_indices[  i  ] = offset + 0;
            cube_indices[i + 1] = offset + 1;
            cube_indices[i + 2] = offset + 2;

            cube_indices[i + 3] = offset + 2;
            cube_indices[i + 4] = offset + 3;
            cube_indices[i + 5] = offset + 0;

            offset += 4; // because each sprite has 4 indices and 6 vertices
        }

        m_IBO = new IndexBuffer(cube_indices, RENDERER3D_INDICES_SIZE);
        glBindVertexArray(0);
    }

    BatchRenderer3D::~BatchRenderer3D()
    {
        delete m_IBO;
        glDeleteBuffers(1, &m_VBO);
    }

    void BatchRenderer3D::begin()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        m_Buffer = (VertexData3D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    }

    void BatchRenderer3D::submit(const Renderable3D* renderable)
    {
        const Transform& transform = renderable->getTransform();
        const maths::vec4& color = renderable->getColor();
        const std::vector<maths::vec2>& uv = renderable->getUV();
        const unsigned int tid = renderable->getTID();
        const Primitive3D& primitive3d = renderable->gerPrimitive();

        maths::mat4 model(1.0f);
        model = maths::mat4::translation(transform.position);
        // TODO: Use Quaternions to rotate the 3D primitive 
        model *= maths::mat4::rotation(transform.rotation.x, maths::vec3(1, 0, 0));
        model *= maths::mat4::rotation(transform.rotation.y, maths::vec3(0, 1, 0));
        model *= maths::mat4::rotation(transform.rotation.z, maths::vec3(0, 0, 1));

        float ts = 0.0f;
        if (tid > 0)
        {
            bool found = false;
            for (int i = 0; i < m_TextureSlots.size(); i++)
            {
                if (m_TextureSlots[i] == tid)
                {
                    ts = (float)(i + 1);
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                if (m_TextureSlots.size() >= 16)
                {
                    end();
                    flush();
                    begin();
                }
                m_TextureSlots.push_back(tid);
                ts = (float)(m_TextureSlots.size());
            }
        }

        // TODO: Query for the primitive and fill the buffer or use the Model<--Mesh to fill the buffer.
        // Here primitive denotes the shape of the renderable to be rendered onto the screen not the actual rendering primitives of the 3D renderable.
        if(primitive3d == Primitive3D::Cube)
        {            
            // Face 1 : Front face
            m_Buffer->vertex = model * maths::vec3(-(transform.scale.x / 2), -(transform.scale.y / 2),  (transform.scale.z / 2));
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

    void BatchRenderer3D::end()
    {
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void BatchRenderer3D::flush()
    {
        shader->enable();
        shader->setUniformMat4("view", m_Camera3D->getViewMatrix());

        for (int i = 0; i < m_TextureSlots.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
        }
        glBindVertexArray(m_VAO);
        m_IBO->bind();

        glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_SHORT, NULL);

        m_IBO->unbind();
        glBindVertexArray(0);

        m_IndicesCount = 0;
        m_TextureSlots.clear();
        shader->disable();
    }

} }