#include "batchrenderer2d.h"

namespace fireworks { namespace graphics {

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
        // TODO: Delete all the textures here (IDK if this works)
        //const int textures_size = m_TextureSlots.size();
        //GLuint textures[textures_size];
        //for(int i = 0; i < textures_size; i++)
        //{
        //    textures[i] = m_TextureSlots[i];
        //}
        //glDeleteTextures(textures_size, textures);

        // Deleting text
        // gltDeleteText(m_Text);
    }

    void BatchRenderer2D::init()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
        glEnableVertexAttribArray(SHADER_UV_INDEX);
        glEnableVertexAttribArray(SHADER_TID_INDEX);
        glEnableVertexAttribArray(SHADER_COLOR_INDEX);
        glVertexAttribPointer(SHADER_VERTEX_INDEX,  3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
        glVertexAttribPointer(SHADER_UV_INDEX,      2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
        glVertexAttribPointer(SHADER_TID_INDEX,     1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(5 * sizeof(GLfloat)));
        glVertexAttribPointer(SHADER_COLOR_INDEX,   4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(6 * sizeof(GLfloat)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);

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

		//for (int i = 0; i < RENDERER_INDICES_SIZE; i += 3)
		//{
		//	tris_indices[i] = offset + 0;
		//	tris_indices[i + 1] = offset + 1;
		//	tris_indices[i + 2] = offset + 2;

		//	offset += 3; // because each tris has 3 indices and 3 vertices
		//}

        m_IBO = new IndexBuffer(quad_indices, RENDERER_INDICES_SIZE);
		//m_TIBO = new IndexBuffer(tris_indices, RENDERER_INDICES_SIZE);

        glBindVertexArray(0);

        // Initialize glText
        gltInit();

        // Creating text
        m_Text = gltCreateText();
    }

    void BatchRenderer2D::begin()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    }

    void BatchRenderer2D::submit(const Renderable2D* renderable)
    {

        const maths::vec3& position = renderable->getPosition();
        const maths::vec2& size = renderable->getSize();
        const maths::vec4& color = renderable->getColor();
		const Primitive2D primitive = renderable->getPrimitive();
        const std::vector<maths::vec2>& uv = renderable->getUV();
        const GLuint tid = renderable->getTID();

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
            // int r = color.x * 255.0f;
            // int g = color.y * 255.0f;
            // int b = color.z * 255.0f;
            // int a = color.w * 255.0f;

            // unsigned int c = a << 24 | b << 16 | g << 8 | r;
        }
        
        if (primitive == Primitive2D::Quad)
        {
            m_Buffer->vertex = *m_TransformationBack * position;
            m_Buffer->uv = uv[0];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = *m_TransformationBack * maths::vec3(position.x, position.y + size.y, position.z);
            m_Buffer->uv = uv[1];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = *m_TransformationBack * maths::vec3(position.x + size.x, position.y + size.y, position.z);
            m_Buffer->uv = uv[2];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_Buffer->vertex = *m_TransformationBack * maths::vec3(position.x + size.x, position.y, position.z);
            m_Buffer->uv = uv[3];
            m_Buffer->tid = ts;
            m_Buffer->color = color;
            m_Buffer++;

            m_IndicesCount += 6;
        }
		else if (primitive == Primitive2D::Triangle)
		{
            std::cerr << "ERROR::BATCH_RENDERER_2D::Batch Renderer 2D does not support triangle primitive" << std::endl;

			//m_Buffer->vertex = *m_TransformationBack * position;
			//m_Buffer->uv = uv[0];
			//m_Buffer->tid = ts;
			//m_Buffer->color = color;
			//m_Buffer++;

			//m_Buffer->vertex = *m_TransformationBack * maths::vec3(position.x + (size.x / 2.0f), position.y + size.y, position.z);
			//m_Buffer->uv = uv[1];
			//m_Buffer->tid = ts;
			//m_Buffer->color = color;
			//m_Buffer++;

			//m_Buffer->vertex = *m_TransformationBack * maths::vec3(position.x + size.x, position.y, position.z);
			//m_Buffer->uv = uv[2];
			//m_Buffer->tid = ts;
			//m_Buffer->color = color;
			//m_Buffer++;

			//m_IndicesCount += 3;
		}
    }

    void BatchRenderer2D::end()
    {
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void BatchRenderer2D::flush()
    {
        m_Shader->enable();
        m_Shader->setUniformMat4("view", m_Camera2D->getViewMatrix());
        for(int i = 0; i < m_TextureSlots.size(); i++)
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
        m_Shader->disable();
    }
} }
