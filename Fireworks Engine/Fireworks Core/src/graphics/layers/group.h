#pragma once

#include "../renderables/renderable2d.h"

namespace fireworks { namespace graphics {

    /// Creates groups of renderables in a hierarchical relative fashion.
    /// 
    /// Adds groups of layers and enables child system to position relatively to each other
    class Group : public Renderable2D
    {
    private:
        std::vector<Renderable2D*> m_Renderables;
        maths::mat4 m_TransformationMatrix;
    public:
        /// Creates a group to position renderables relatively.
        /// 
        /// @param transform The relative position of the group relative to the parent group/layer
        /// @note Using this transform matrix we can add renderables relative to one another
        Group(const maths::mat4& transform);
        ~Group();
        /// Adds renderables to this group
        /// 
        /// @note Any renderables will be positioned relative to this group and not as per the world position
        void add(Renderable2D* renderable);
        /// Submits the group to the Renderer Queue
        void submit(Renderer2D* renderer) const override;
    };
} }
