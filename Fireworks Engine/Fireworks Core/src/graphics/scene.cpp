#include "scene.h"

namespace fireworks { namespace graphics {

    Scene::Scene(Renderer3D* renderer)
        :m_Renderer(renderer)
    {

    }

    Scene::~Scene()
    {
        delete m_Renderer;
        for (int i = 0; i < m_Renderables.size(); i++)
        {
            delete m_Renderables[i];
        }
    }

    void Scene::add(Renderable3D* renderable)
    {
        m_Renderables.push_back(renderable);
    }

    void Scene::render()
    {
        if (dynamic_cast<BatchRenderer3D*>(m_Renderer))
        {
            m_Renderer->begin();
            for (const Renderable3D* renderable : m_Renderables)
            {
                renderable->submit(m_Renderer);
            }
            m_Renderer->end();
            m_Renderer->flush();
        }
    }

} }
