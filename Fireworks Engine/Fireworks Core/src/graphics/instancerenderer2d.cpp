#include "instancerenderer2d.h"

namespace fireworks { namespace graphics {

	
	InstanceRenderer2D::InstanceRenderer2D(Camera2D* camera2D)
		: Renderer2D(camera2D)
	{
		init();
	}

	InstanceRenderer2D::~InstanceRenderer2D()
	{
		delete m_IBO;
		glDeleteBuffers(1, &m_VBO);
	}

	void InstanceRenderer2D::init()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, INSTANCE_RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);
		glVertexAttribPointer(SHADER_VERTEX_INDEX,	3, GL_FLOAT, GL_FALSE, INSTANCE_RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_UV_INDEX,		2, GL_FLOAT, GL_FALSE, INSTANCE_RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
		glVertexAttribPointer(SHADER_TID_INDEX,		1, GL_FLOAT, GL_FALSE, INSTANCE_RENDERER_VERTEX_SIZE, (const GLvoid*)(5 * sizeof(GLfloat)));
		glVertexAttribPointer(SHADER_COLOR_INDEX,	4, GL_FLOAT, GL_FALSE, INSTANCE_RENDERER_VERTEX_SIZE, (const GLvoid*)(6 * sizeof(GLfloat)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLushort indices[INSTANCE_RENDERER_INDICES_SIZE];

		for (int i = 0; i < INSTANCE_RENDERER_INDICES_SIZE; i += 6)
		{
			indices[  i  ] = 0;
			indices[i + 1] = 1;
			indices[i + 2] = 2;

			indices[i + 3] = 2;
			indices[i + 4] = 3;
			indices[i + 5] = 0;
		}

		m_IBO = new IndexBuffer(indices, INSTANCE_RENDERER_INDICES_SIZE);

		glBindVertexArray(0);
	}

	void InstanceRenderer2D::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void InstanceRenderer2D::submit(const Renderable2D* renderable)
	{
		// This position is used to set the initial position of the RigidBody 
		// except for this we have no use of it
		const maths::vec3& position =renderable->getPosition();
		const float& rotation = renderable->getRotation();
		const maths::vec2& size = renderable->getSize();
		const maths::vec4& color = renderable->getColor();
		const Primitive2D primitive = renderable->getPrimitive();
		const std::vector<maths::vec2>& uv = renderable->getUV();
		const GLuint tid = renderable->getTID();
		const std::vector<components::Component*> components = renderable->components;

		renderable->shader->enable();
		renderable->shader->setUniformMat4("view", m_Camera2D->getViewMatrix());

		renderable->shader->setUniform1i("flipX", renderable->flippedX);
		renderable->shader->setUniform1i("flipY", renderable->flippedY);

		
		maths::mat4 model(1.0f);
		model = maths::mat4::translation(position);
		model *= maths::mat4::rotation(maths::toDegrees(rotation), maths::vec3(0, 0, 1));

		m_Texture = renderable->getTID(); // Redundant (IDK if the renderer should cache the current texture as well)
		float ts = 0;
		if (tid > 0)
			ts = 1.0f;

		if (primitive == Primitive2D::Quad)
		{
			m_Buffer->vertex = *m_TransformationBack * model * maths::vec3(- (size.x / 2),- (size.y / 2), position.z);
			m_Buffer->uv = uv[0];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * model * maths::vec3(- (size.x / 2),-(size.y / 2) + size.y, position.z);
			m_Buffer->uv = uv[1];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * model * maths::vec3(-(size.x / 2) + size.x, - (size.y / 2) + size.y, position.z);
			m_Buffer->uv = uv[2];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * model * maths::vec3(-(size.x / 2) + size.x, - (size.y / 2), position.z);
			m_Buffer->uv = uv[3];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_IndicesCount += 6;
		}
		else if (primitive == Primitive2D::Triangle)
		{
			m_Buffer->vertex = *m_TransformationBack * model * maths::vec3( - (size.x / 2), - (size.y / 2), 0);
			m_Buffer->uv = uv[0];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * model * maths::vec3( + (size.x / 2.0f) - (size.x / 2),  + size.y - (size.y / 2), position.z);
			m_Buffer->uv = uv[1];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * model * maths::vec3( + size.x - (size.x / 2), - (size.y / 2), position.z);
			m_Buffer->uv = uv[2];
			m_Buffer->tid = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_IndicesCount += 3;
		}
	}

	void InstanceRenderer2D::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void InstanceRenderer2D::flush()
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

