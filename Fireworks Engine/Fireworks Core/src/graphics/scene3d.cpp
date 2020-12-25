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
                if (!dynamic_cast<Model*>(renderable) && renderable)
                {
                    renderable->submit(renderer);
                }
                if (dynamic_cast<Model*>(renderable))
                {
                    // Render the queued renderables onto the screen immediately
                    renderer->end();
                    renderer->flush();

                    // TODO(High priority!!!): Currently all 3D models are rendered using per
                    // draw call, Enable batching of Models/Meshes based on some similarity 
                    // factors such as same IBOs etc.
                    /*
                     * As soon as we encounter a Model we flush all the previously stashed Meshes
                     * but the Model is rendered on a per draw call basis due to their variation
                     * in IBOs, but if the IBOs of the models are same we queue them to render
                     * and draw them using a single draw call. 
                     * 
                     * Hence similar IBO meshes are rendered using a single draw call(of course,
                     * this is dependent on the texture slots, and that's a whole other thing but
                     * we get the basic idea right?)
                     * 
                     * Hence find a way to sort and group the renderables in the scene based on
                     * IBOs, if possible give this job to the renderer.
                     * 
                     * To batch models with different IBOs into their respective mini-batches we
                     * assign batch IDs to recognize their differences and use a much more 
                     * optimized algorithm to create those sub batches in a contiguous space in
                     * the render queue.
                     * 
                     * (Not using a contiguous batching can result in delayed rendering, 
                     * moreover using pre sorted batches before starting the rendering will 
                     * optimize the renderer and make dynamically added renderables sort much 
                     * faster into their respective batches)
                     * 
                     * Once we do that we can check for the batch ID and once that changes we
                     * flush the submitted renderables.
                     */
                    // Now freshly submit the model and render it using the custom IBO
                    renderer->begin();
                    renderable->submit(renderer);
                    renderer->end();
                    renderable->flush(renderer, dynamic_cast<Model*>(renderable)->modelIBO);
                    // To enable submission for the remaining renderables in the render queue
                    renderer->begin();
                }
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
