#include "layer.h"

namespace fireworks { namespace graphics {
    // TODO: fix the implementations according to the renderer being used
    Layer::Layer(Renderer2D* renderer)
        : m_Renderer(renderer)
    {
		
    }

    Layer::~Layer()
    {
        delete m_Renderer;

        for(int i = 0; i < m_Renderables.size(); i++)
        {
            delete m_Renderables[i];
        }
    }

    void Layer::add(Renderable2D* renderable)
    {
        if (dynamic_cast<InstanceRenderer2D*>(m_Renderer))
        {
            renderable->m_Shader->setUniformMat4("projection", m_Renderer->m_Camera2D->getProjectionMatrix());
        }
        m_Renderables.push_back(renderable);
    }

    void Layer::render()
    {
        if (dynamic_cast<BatchRenderer2D*>(m_Renderer))
        {
		    m_Renderer->begin();
		    for (const Renderable2D* renderable : m_Renderables)
		    {
			    renderable->submit(m_Renderer);
		    }
		    m_Renderer->end();
		    m_Renderer->flush();
        }
        else if(dynamic_cast<InstanceRenderer2D*>(m_Renderer))
        {
			for (const Renderable2D* renderable : m_Renderables)
			{
				m_Renderer->begin();
				renderable->m_Shader->enable();
				renderable->m_Shader->setUniformMat4("view", m_Renderer->m_Camera2D->getViewMatrix());

				renderable->submit(m_Renderer);
				m_Renderer->end();
				m_Renderer->flush();
			}
        }

    }

} }


