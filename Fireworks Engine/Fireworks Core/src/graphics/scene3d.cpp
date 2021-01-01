#include "scene3d.h"

namespace fireworks { namespace graphics {

    Scene3D::Scene3D(Renderer3D* renderer)
        : renderer(renderer)
    {

    }

    Scene3D::~Scene3D()
    {
        delete renderer;
        for (int i = 0; i < renderables.size(); i++)
        {
            delete renderables[i];
        }
    }

    void Scene3D::add(Renderable3D* renderable)
    {
        if (dynamic_cast<ShotRenderer3D*>(renderer))
        {
            glm::mat4 proj = glm::perspective(renderer->m_Camera3D->FOV, renderer->m_Camera3D->aspectRatio, renderer->m_Camera3D->nearClipping, renderer->m_Camera3D->farClipping);

            renderable->shader->setUniformglmMat4("projection", proj);
        }
        renderables.push_back(renderable);
    }

    void Scene3D::render()
    {
        if (dynamic_cast<BatchRenderer3D*>(renderer))
        {
            renderer->begin();
            for (Renderable3D* renderable : renderables)
            {
                renderable->submit(renderer);
            }
            renderer->end();
            renderer->flush();
        }
        else if (dynamic_cast<ShotRenderer3D*>(renderer))
        {
            for (const Renderable3D* renderable : renderables)
            {
                renderer->begin();
                renderable->shader->enable();
                renderable->shader->setUniformMat4("view", renderer->m_Camera3D->getViewMatrix());

                renderable->submit(renderer);
                renderer->end();
                renderer->flush();
            }
        }
    }

} }
