#include "batchrenderer3d.h"
#include <algorithm>
namespace fireworks { namespace graphics {
    
    std::uint32_t Renderable3D::m_UniqueID = 0;

    BatchRenderer3D::BatchRenderer3D(PerspectiveCamera* camera3D, Shader* shader)
        : Renderer3D(camera3D), shader(shader)
    {
        init();
        this->shader->enable();
        this->shader->setUniformMat4("projection", camera3D->getProjectionMatrix());

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
        GLCall(glGenVertexArrays(1, &m_VAO));
        GLCall(glGenBuffers(1, &m_VBO));

        GLCall(glBindVertexArray(m_VAO));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
        GLCall(glBufferData(GL_ARRAY_BUFFER, RENDERER3D_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW));
        GLCall(glEnableVertexAttribArray(SHADER_VERTEX_INDEX));
        GLCall(glEnableVertexAttribArray(SHADER_UV_INDEX));
        GLCall(glEnableVertexAttribArray(SHADER_TID_INDEX));
        GLCall(glEnableVertexAttribArray(SHADER_COLOR_INDEX));
        GLCall(glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER3D_VERTEX_SIZE, (const GLvoid*)0));
        GLCall(glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER3D_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat))));
        GLCall(glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER3D_VERTEX_SIZE, (const GLvoid*)(5 * sizeof(GLfloat))));
        GLCall(glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER3D_VERTEX_SIZE, (const GLvoid*)(6 * sizeof(GLfloat))));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        m_IBO = new IndexBuffer(nullptr, RENDERER3D_INDICES_SIZE);
        GLCall(glBindVertexArray(0));
    }

    BatchRenderer3D::~BatchRenderer3D()
    {
        delete m_IBO;
        glDeleteBuffers(1, &m_VBO);
    }

    void BatchRenderer3D::begin()
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
        m_Buffer = (VertexData3D*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    }

    void BatchRenderer3D::submit(const Renderable3D* renderable)
    {
        const Transform& transform = renderable->getTransform();
        const glm::vec4& color = renderable->getColor();
        const std::vector<glm::vec2>& uv = renderable->getUV();
        const unsigned int tid = renderable->getTID();
        const Primitive3D& primitive3d = renderable->gerPrimitive();
        std::vector<VertexData3D> vertices = renderable->getVerts();
        std::vector<GLushort> indices = renderable->getInidces();

        indexOffset += renderable->getVertsSize();

        glm::mat4 model(1.0f);
        model = glm::translate(model, transform.position);
        // TODO: Use Quaternions to rotate the 3D primitive 
		model *= glm::rotate(model, transform.rotation.x, glm::vec3(1, 0, 0));
		model *= glm::rotate(model, transform.rotation.y, glm::vec3(0, 1, 0));
		model *= glm::rotate(model, transform.rotation.z, glm::vec3(0, 0, 1));

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

        for (int i = 0; i < renderable->getVertsSize(); i++)
        {
            // TODO: Make sure the vertices are Clockwise generated in case we use front face culling.
            m_Buffer->vertex = (model * glm::vec4(vertices[i].vertex.x, vertices[i].vertex.y, vertices[i].vertex.z, 1.0f));
            m_Buffer->uv = vertices[i].uv;
            m_Buffer->tid = ts;
            m_Buffer->color = vertices[i].color;
            m_Buffer++;
        }

        /*
         * Test and fix this problem, that to every new index added into the pool
         * a pool offset must be added because now all the vertices are pooled together
         * so the Indices must also start from the nth vertex and not from 0 in the pool.
         * We add the previous renderables maxVertexCounts + 1.
         * TODO: Fix this by pre querying the offset, do not do this every frame, we will deal
         * with dynamic render queue changes later.
         * Use static and dynamic batch dispatching design to resolve this issue
         */
  
        if (m_IndicesPool.size())
        {
            int largest_element = m_IndicesPool[0];
            for (int i = 1; i < m_IndicesPool.size(); i++)  //start iterating from the second element
            {
                if (m_IndicesPool[i] > largest_element)
                {
                    largest_element = m_IndicesPool[i];
                }
            }
            //std::cout << "Max Element in the pool is : " << largest_element << std::endl;

            for (int i = 0; i < indices.size(); i++)
            {
                indices[i] += largest_element + 1;
            }   
        }

        m_IndicesPool.insert(m_IndicesPool.end(), indices.begin(), indices.end());
        m_IndicesCount += renderable->getIndicesSize();
    } 

    void BatchRenderer3D::end()
    {
        GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        m_IBO->bind();
        GLushort* m_IndexBuffer = (GLushort*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);

        if (m_IndexBuffer == nullptr)
        {
            std::cout << "ERROR::OPENGL:: Index Buffer mappping cannot be done propoerly" << std::endl;
            return;
        }

        for (int i = 0; i < m_IndicesPool.size(); i++)
        {
            *m_IndexBuffer = m_IndicesPool[i];
            m_IndexBuffer++;
        }

        GLCall(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER));
        m_IBO->unbind();
    }

    void BatchRenderer3D::flush()
    {
        m_IndicesPool.clear();
        shader->enable();
        shader->setUniformMat4("view", m_Camera3D->getViewMatrix());

        for (int i = 0; i < m_TextureSlots.size(); i++)
        {
            GLCall(glActiveTexture(GL_TEXTURE0 + i));
            GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]));
        }

        GLCall(glBindVertexArray(m_VAO)); 
        m_IBO->bind();

        GLCall(glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_SHORT, NULL));
        //GLCall(glDrawArrays(GL_POINTS, 0, 10000));

        m_IBO->unbind();

        GLCall(glBindVertexArray(0));

        m_IndicesCount = 0;
        indexOffset = 0;
        m_TextureSlots.clear();
        shader->disable();
    }
} }