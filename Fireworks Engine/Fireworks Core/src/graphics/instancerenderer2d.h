#pragma once

#include "renderables/renderable2d.h"
#include "renderer2d.h"
#include "../components/component.h"

namespace fireworks { namespace graphics {

#define INSTANCE_RENDERER_MAX_SPRITES    1
#define INSTANCE_RENDERER_VERTEX_SIZE    sizeof(VertexData)
#define INSTANCE_RENDERER_SPRITE_SIZE    INSTANCE_RENDERER_VERTEX_SIZE * 4
#define INSTANCE_RENDERER_BUFFER_SIZE    INSTANCE_RENDERER_SPRITE_SIZE * INSTANCE_RENDERER_MAX_SPRITES
#define INSTANCE_RENDERER_INDICES_SIZE   INSTANCE_RENDERER_MAX_SPRITES * 6

	class InstanceRenderer2D : public Renderer2D
	{
	private:
		GLuint          m_VAO;
		GLuint          m_VBO;
		VertexData*		m_Buffer;
		IndexBuffer*	m_IBO;
		GLsizei         m_IndicesCount;
		GLuint			m_Texture;
	public:
		InstanceRenderer2D(Camera2D* camera);
		~InstanceRenderer2D();

		void begin() override;
		void submit(const Renderable2D* renderable) override;
		void end() override;
		void flush() override;
private:
	void init();

	};

} }