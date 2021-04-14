#include "batchrenderer2d.h"

namespace fireworks { namespace graphics {

	std::uint32_t Renderable2D::m_UniqueID = 0;

    BatchRenderer2D::BatchRenderer2D(Camera2D* camera2D, Shader* shader)
        :Renderer2D(camera2D), m_Shader(shader)
    {
        init();
        m_Shader->setUniformMat4("projection", m_Camera2D->getProjectionMatrix());
        m_Shader->enable();
		GLint texIDs[] =
		{
			0, 1,  2,  3,  4,  5,  6,  7,
			8, 9, 10, 11, 12, 13, 14, 15
		};
        m_Shader->setUniform1iv("textures", texIDs, 8);
        m_Shader->disable();
    }

    BatchRenderer2D::~BatchRenderer2D()
    {
        delete m_IBO;
        glDeleteBuffers(1, &m_VBO);
        glDeleteTextures(m_TextureSlots.size(), &(m_TextureSlots)[0]);
    }

    void BatchRenderer2D::init()
    {
        GLCall(glGenVertexArrays(1, &m_VAO));
        GLCall(glGenBuffers(1, &m_VBO));

        GLCall(glBindVertexArray(m_VAO));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
        GLCall(glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW));
        GLCall(glEnableVertexAttribArray(SHADER_VERTEX_INDEX));
        GLCall(glEnableVertexAttribArray(SHADER_UV_INDEX));
        GLCall(glEnableVertexAttribArray(SHADER_TID_INDEX));
        GLCall(glEnableVertexAttribArray(SHADER_COLOR_INDEX));
        GLCall(glVertexAttribPointer(SHADER_VERTEX_INDEX,  3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0));
        GLCall(glVertexAttribPointer(SHADER_UV_INDEX,      2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat))));
        GLCall(glVertexAttribPointer(SHADER_TID_INDEX,     1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(5 * sizeof(GLfloat))));
        GLCall(glVertexAttribPointer(SHADER_COLOR_INDEX,   4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(6 * sizeof(GLfloat))));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        int offset = 0;
        for(int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
        {
            quad_indices[  i  ] = offset + 0;
            quad_indices[i + 1] = offset + 1;
            quad_indices[i + 2] = offset + 2;

            quad_indices[i + 3] = offset + 2;
            quad_indices[i + 4] = offset + 3;
            quad_indices[i + 5] = offset + 0;

            offset += 4; // because each sprite has 4 indices and 6 vertices
        }

        m_IBO = new IndexBuffer(quad_indices, RENDERER_INDICES_SIZE);

        GLCall(glBindVertexArray(0));
    }

    void BatchRenderer2D::begin()
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
        m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    }

    void BatchRenderer2D::submit(const Renderable2D* renderable)
    {

        const glm::vec3& position = renderable->getPosition();
		const float& rotation = renderable->getRotation();
        const glm::vec2& size = renderable->getSize();
        const glm::vec4& color = renderable->getColor();
		const Primitive2D primitive = renderable->getPrimitive();
        const std::vector<glm::vec2>& uv = renderable->getUV();
        const GLuint tid = renderable->getTID();
		const std::vector<components::Component*> components = renderable->components;

		
		glm::mat4 model(1.0f);
		model = glm::translate(model, position);
		model *= glm::rotate(model, glm::degrees(rotation), glm::vec3(0, 0, 1));

        float ts = 0.0f;
        if(tid > 0)
        {
            bool found = false;
            for(int i = 0; i < m_TextureSlots.size(); i++)
            {
                if(m_TextureSlots[i] == tid)
                {
                    ts = (float)(i + 1);
                    found = true;
                    break;
                }
            }

            if(!found)
            {
                if(m_TextureSlots.size() >= 16)
                {
                    end();
                    flush();
                    begin();
                }
                m_TextureSlots.push_back(tid);
                ts = (float)(m_TextureSlots.size());
            }
        }
        else
        {
            // TODO: use hex for vertex colors
            // int r = color.x * 255.0f;
            // int g = color.y * 255.0f;
            // int b = color.z * 255.0f;
            // int a = color.w * 255.0f;

            // unsigned int c = a << 24 | b << 16 | g << 8 | r;
        }
        
        if (primitive == Primitive2D::Quad)
        {
			m_Buffer->vertex = *m_TransformationBack * model * glm::vec4(-(size.x / 2), -(size.y / 2), position.z, 1.0f);
			m_Buffer->uv = uv[0];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * model * glm::vec4(-(size.x / 2), -(size.y / 2) + size.y, position.z, 1.0f);
			m_Buffer->uv = uv[1];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * model * glm::vec4(-(size.x / 2) + size.x, -(size.y / 2) + size.y, position.z, 1.0f);
			m_Buffer->uv = uv[2];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * model * glm::vec4(-(size.x / 2) + size.x, -(size.y / 2), position.z, 1.0f);
			m_Buffer->uv = uv[3];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

            m_IndicesCount += 6;
        }
		else if (primitive == Primitive2D::Triangle)
		{
            std::cerr << "ERROR::BATCH_RENDERER_2D::Batch Renderer 2D does not support triangle primitives, yet!" << std::endl;
		}
    }

    void BatchRenderer2D::end()
    {
        GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void BatchRenderer2D::flush()
    {
        m_Shader->enable();
        m_Shader->setUniformMat4("view", m_Camera2D->getViewMatrix());
        for(int i = 0; i < m_TextureSlots.size(); i++)
        {
            GLCall(glActiveTexture(GL_TEXTURE0 + i));
            GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]));
        }
        GLCall(glBindVertexArray(m_VAO));
        m_IBO->bind();

        GLCall(glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_SHORT, NULL));

        m_IBO->unbind();
        GLCall(glBindVertexArray(0));

        m_IndicesCount = 0;
        m_TextureSlots.clear();
        m_Shader->disable();
    }
} }
